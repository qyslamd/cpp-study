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
  std::unique_lock<std::mutex> lockGrow{_lockGrow};  // �Զ�������
#endif
  // �����߳�����,�������� Ԥ�������� THREADPOOL_MAX_NUM
  for (; thread_list.size() < THREADPOOL_MAX_NUM && size > 0; --size) {
    thread_list.emplace_back(
        [this] {  // �����̺߳���
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
        task();
#ifdef THREADPOOL_AUTO_GROW
        if (idel_num > 0 &&
            thread_list.size() >
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

}  // namespace thread_pool