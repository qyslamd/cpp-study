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
    using ushort = unsigned short;
class threadpool {
  ushort thread_size;
  using Task = std::function<void()>;
  std::vector<std::thread> thread_list;
  std::queue<Task> task_queue;
  std::mutex mutex_lock;  // 任务队列同步锁
#ifdef THREADPOOL_AUTO_GROW
  std::mutex _lockGrow;  // 线程池增长同步锁
#endif
  std::condition_variable _task_cv;  // 条件阻塞
  std::atomic<bool> _run{true};      // 线程池是否执行
  std::atomic<int> idel_num{0};      // 空闲线程数量

 public:
  explicit threadpool(ushort size = 4);
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

    // 函数 f 的返回值类型
    using RetType = decltype(f(args...));
    // typename std::result_of<F(Args...)>::type,

    // 把函数入口及参数,打包(绑定)
    auto task = make_shared<std::packaged_task<RetType()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<RetType> future = task->get_future();

    // 添加任务到队列
    {
      // 对当前块的语句加锁  lock_guard 是 mutex 的 stack
      std::lock_guard<std::mutex> lock{mutex_lock};

      task_queue.emplace([task]() { (*task)(); });
    }
#ifdef THREADPOOL_AUTO_GROW
    if (idel_num < 1 && thread_list.size() < THREADPOOL_MAX_NUM)
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
    if (idel_num < 1 && thread_list.size() < THREADPOOL_MAX_NUM)
      addThread(1);
#endif  // !THREADPOOL_AUTO_GROW
    _task_cv.notify_one();
  }

  inline int idlCount() { return idel_num; }
  inline int threadCount() { return thread_list.size(); }

#ifndef THREADPOOL_AUTO_GROW
 private:
#endif
  void addThread(ushort size);
};

}  // namespace thread_pool