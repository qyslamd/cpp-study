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
  unsigned short thread_size;          // ��ʼ���߳�����
  using Task = std::function<void()>;  // ��������
  std::vector<std::thread> _pool;           // �̳߳�
  std::queue<Task> task_queue;             // �������
  std::mutex mutex_lock;                    // �������ͬ����
#ifdef THREADPOOL_AUTO_GROW
  std::mutex _lockGrow;              // �̳߳�����ͬ����
#endif                               // !THREADPOOL_AUTO_GROW
  std::condition_variable _task_cv;  // ��������
  std::atomic<bool> _run{true};      // �̳߳��Ƿ�ִ��
  std::atomic<int> idel_num{0};      // �����߳�����

 public:
  explicit threadpool(unsigned short size = 4);
  ~threadpool();

 public:
  // �ύһ������
  // ����.get()��ȡ����ֵ��ȴ�����ִ����,��ȡ����ֵ
  // �����ַ�������ʵ�ֵ������Ա��
  // һ����ʹ��   bind�� .commit(std::bind(&Dog::sayHello, &dog));
  // һ������   mem_fn�� .commit(std::mem_fn(&Dog::sayHello), this)
  template <class F, class... Args>
  auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    if (!_run)  // stoped ??
      throw runtime_error("commit on ThreadPool is stopped.");

    using RetType =
        decltype(f(args...));  // typename std::result_of<F(Args...)>::type,
                               // ���� f �ķ���ֵ����
    auto task = make_shared<std::packaged_task<RetType()>>(
        std::bind(std::forward<F>(f),
             std::forward<Args>(args)...));  // �Ѻ�����ڼ�����,���(��)
    std::future<RetType> future = task->get_future();
    {  // ������񵽶���
      std::lock_guard<std::mutex> lock{
          std::mutex_lock};  // �Ե�ǰ���������  lock_guard �� mutex �� stack
                   // ��װ�࣬�����ʱ�� lock()��������ʱ�� unlock()
      task_queue.emplace([task]() {  // push(Task{...}) �ŵ����к���
        (*task)();
      });
    }
#ifdef THREADPOOL_AUTO_GROW
    if (_idlThrNum < 1 && _pool.size() < THREADPOOL_MAX_NUM)
      addThread(1);
#endif                      // !THREADPOOL_AUTO_GROW
    _task_cv.notify_one();  // ����һ���߳�ִ��

    return future;
  }
  // �ύһ���޲�����, ���޷���ֵ
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
  // �����߳�����
  inline int idlCount() { return idel_num; }
  // �߳�����
  inline int thrCount() { return _pool.size(); }

#ifndef THREADPOOL_AUTO_GROW
 private:
#endif  // !THREADPOOL_AUTO_GROW
        // ���ָ���������߳�
  void addThread(unsigned short size) {
#ifdef THREADPOOL_AUTO_GROW
    if (!_run)  // stoped ??
      throw std::runtime_error("Grow on ThreadPool is stopped.");
    std::unique_lock<std::mutex> lockGrow{_lockGrow};  // �Զ�������
#endif                                       // !THREADPOOL_AUTO_GROW
    for (; _pool.size() < THREADPOOL_MAX_NUM && size > 0;
         --size) {  // �����߳�����,�������� Ԥ�������� THREADPOOL_MAX_NUM
      _pool.emplace_back([this] {  // �����̺߳���
        while (true)  // ��ֹ _run==false ʱ��������,��ʱ������п��ܲ�Ϊ��
        {
          Task task;  // ��ȡһ����ִ�е� task
          {
            // unique_lock ��� lock_guard �ĺô��ǣ�������ʱ unlock() �� lock()
            std::unique_lock<std::mutex> lock{mutex_lock};
            _task_cv.wait(lock, [this] {  // wait ֱ���� task, ����Ҫֹͣ
              return !_run || !task_queue.empty();
            });
            if (!_run && task_queue.empty())
              return;
            idel_num--;
            task = move(task_queue.front());  // ���Ƚ��ȳ��Ӷ���ȡһ�� task
            task_queue.pop();
          }
          task();  // ִ������
#ifdef THREADPOOL_AUTO_GROW
          if (idel_num > 0 &&
              _pool.size() >
                  idel_num)  // ֧���Զ��ͷſ����߳�,�����ֵ������������߳�
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