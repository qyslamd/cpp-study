#include "thread_pool.hpp"

namespace thread_pool {
threadpool ::threadpool(ushort size) : thread_size(size) {
  addThread(size);
}

threadpool::~threadpool() {
  _run = false;
  _task_cv.notify_all();
  for (std::thread& thread : thread_list) {
    if (thread.joinable())
      thread.join();
  }
}

  void threadpool::addThread(ushort size) {
#ifdef THREADPOOL_AUTO_GROW
  if (!_run)
    throw std::runtime_error("Grow on ThreadPool is stopped.");
  std::unique_lock<std::mutex> lockGrow{_lockGrow};  // 自动增长锁
#endif
  // 增加线程数量,但不超过 预定义数量 THREADPOOL_MAX_NUM
  for (; thread_list.size() < THREADPOOL_MAX_NUM && size > 0; --size) {
    thread_list.emplace_back(
        [this] {  // 工作线程函数
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
        task();
#ifdef THREADPOOL_AUTO_GROW
        if (idel_num > 0 &&
            thread_list.size() >
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

}  // namespace thread_pool