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
  std::mutex mutex_lock;  // �������ͬ����
#ifdef THREADPOOL_AUTO_GROW
  std::mutex _lockGrow;  // �̳߳�����ͬ����
#endif
  std::condition_variable _task_cv;  // ��������
  std::atomic<bool> _run{true};      // �̳߳��Ƿ�ִ��
  std::atomic<int> idel_num{0};      // �����߳�����

 public:
  explicit threadpool(ushort size = 4);
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

    // ���� f �ķ���ֵ����
    using RetType = decltype(f(args...));
    // typename std::result_of<F(Args...)>::type,

    // �Ѻ�����ڼ�����,���(��)
    auto task = make_shared<std::packaged_task<RetType()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<RetType> future = task->get_future();

    // ������񵽶���
    {
      // �Ե�ǰ���������  lock_guard �� mutex �� stack
      std::lock_guard<std::mutex> lock{mutex_lock};

      task_queue.emplace([task]() { (*task)(); });
    }
#ifdef THREADPOOL_AUTO_GROW
    if (idel_num < 1 && thread_list.size() < THREADPOOL_MAX_NUM)
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