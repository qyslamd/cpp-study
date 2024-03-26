#pragma once

#include <atomic>
#include <future>
#include <queue>
#include <vector>
#include <condition_variable>
#include <thread>
#include <functional>
#include <stdexcept>

#ifndef THREADPOOL_MAX_NUM
#define THREADPOOL_MAX_NUM 16
#endif

#ifndef THREADPOOL_AUTO_GROW
#define THREADPOOL_AUTO_GROW 1
#endif

namespace thread_pool {
class threadpool {
  unsigned short thread_size;          // 初始化线程数量
  using Task = std::function<void()>;  // 定义类型
  std::vector<std::thread> _pool;           // 线程池
  std::queue<Task> task_queue;             // 任务队列
  std::mutex mutex_lock;                    // 任务队列同步锁
#ifdef THREADPOOL_AUTO_GROW
  std::mutex _lockGrow;              // 线程池增长同步锁
#endif                               // !THREADPOOL_AUTO_GROW
  std::condition_variable _task_cv;  // 条件阻塞
  std::atomic<bool> _run{true};      // 线程池是否执行
  std::atomic<int> idel_num{0};      // 空闲线程数量

 public:
  explicit threadpool(unsigned short size = 4);
  ~threadpool();

 public:
  // 提交一个任务
  // 调用.get()获取返回值会等待任务执行完,获取返回值
  // 有两种方法可以实现调用类成员，
  // 一种是使用   bind： .commit(std::bind(&Dog::sayHello, &dog));
  // 一种是用   mem_fn： .commit(std::mem_fn(&Dog::sayHello), this)
  template <class F, class... Args>
  auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    if (!_run)  // stoped ??
      throw runtime_error("commit on ThreadPool is stopped.");

    using RetType =
        decltype(f(args...));  // typename std::result_of<F(Args...)>::type,
                               // 函数 f 的返回值类型
    auto task = make_shared<std::packaged_task<RetType()>>(
        std::bind(std::forward<F>(f),
             std::forward<Args>(args)...));  // 把函数入口及参数,打包(绑定)
    std::future<RetType> future = task->get_future();
    {  // 添加任务到队列
      std::lock_guard<std::mutex> lock{
          std::mutex_lock};  // 对当前块的语句加锁  lock_guard 是 mutex 的 stack
                   // 封装类，构造的时候 lock()，析构的时候 unlock()
      task_queue.emplace([task]() {  // push(Task{...}) 放到队列后面
        (*task)();
      });
    }
#ifdef THREADPOOL_AUTO_GROW
    if (_idlThrNum < 1 && _pool.size() < THREADPOOL_MAX_NUM)
      addThread(1);
#endif                      // !THREADPOOL_AUTO_GROW
    _task_cv.notify_one();  // 唤醒一个线程执行

    return future;
  }
  // 提交一个无参任务, 且无返回值
  template <class F>
  void commit2(F&& task) {
    if (!_run)
      return;
    {
      lock_guard<mutex> lock{mutex_lock};
      task_queue.emplace(std::forward<F>(task));
    }
#ifdef THREADPOOL_AUTO_GROW
    if (_idlThrNum < 1 && _pool.size() < THREADPOOL_MAX_NUM)
      addThread(1);
#endif  // !THREADPOOL_AUTO_GROW
    _task_cv.notify_one();
  }
  // 空闲线程数量
  inline int idlCount() { return idel_num; }
  // 线程数量
  inline int thrCount() { return _pool.size(); }

#ifndef THREADPOOL_AUTO_GROW
 private:
#endif  // !THREADPOOL_AUTO_GROW
        // 添加指定数量的线程
  void addThread(unsigned short size) {
#ifdef THREADPOOL_AUTO_GROW
    if (!_run)  // stoped ??
      throw std::runtime_error("Grow on ThreadPool is stopped.");
    std::unique_lock<std::mutex> lockGrow{_lockGrow};  // 自动增长锁
#endif                                       // !THREADPOOL_AUTO_GROW
    for (; _pool.size() < THREADPOOL_MAX_NUM && size > 0;
         --size) {  // 增加线程数量,但不超过 预定义数量 THREADPOOL_MAX_NUM
      _pool.emplace_back([this] {  // 工作线程函数
        while (true)  // 防止 _run==false 时立即结束,此时任务队列可能不为空
        {
          Task task;  // 获取一个待执行的 task
          {
            // unique_lock 相比 lock_guard 的好处是：可以随时 unlock() 和 lock()
            std::unique_lock<std::mutex> lock{mutex_lock};
            _task_cv.wait(lock, [this] {  // wait 直到有 task, 或需要停止
              return !_run || !task_queue.empty();
            });
            if (!_run && task_queue.empty())
              return;
            idel_num--;
            task = move(task_queue.front());  // 按先进先出从队列取一个 task
            task_queue.pop();
          }
          task();  // 执行任务
#ifdef THREADPOOL_AUTO_GROW
          if (idel_num > 0 &&
              _pool.size() >
                  idel_num)  // 支持自动释放空闲线程,避免峰值过后大量空闲线程
            return;
#endif  // !THREADPOOL_AUTO_GROW
          {
            std::unique_lock<std::mutex> lock{mutex_lock};
            idel_num++;
          }
        }
      });
      {
        std::unique_lock<std::mutex> lock{mutex_lock};
        idel_num++;
      }
    }
  }
};

}  // namespace thread_pool