#pragma once

#include <atomic>
#include <future>
#include <queue>
#include <vector>
#include <condition_variable>
#include <thread>
#include <functional>
#include <stdexcept>
#include <iostream>

#ifndef THREADPOOL_MAX_NUM
#define THREADPOOL_MAX_NUM 16
#endif

namespace thread_usage {
void execute();

struct BasicThread {
  static auto thread_demo() -> void;
  static auto mutex_lock_demo() -> void;
  static auto condition_variable_demo() -> void;
  static auto promise_demo() -> void;
  static auto packaged_task_demo() -> void;
  static auto async_demo() -> void;
  static auto call_once_demo() -> void;
};

class ThreadPool1;
struct ThreadAvanced {
  // �ϱߵ�ѧ���ˣ����Կ�ʼдһ���̳߳��ˡ�
  static auto thread_pool_demo() -> void;
};


/*
 * ʹ��C++11ʵ��һ���̳߳صĲ��輰˼·����
 * 1.һ���������̵߳��̶߳��� thread_list
 * 2.һ������������������ task_list
 * 3.�������������� commit_task()
 * 4.�̶߳����е��̻߳ᰴ��Ԥ�����ԣ�����FIFO���Ӷ�����ȡ������ִ�У�һ��û���������������ȴ���������ʱ���ѡ�
 * 5.�߳�ִ������ʱ������ѭ�̳߳صĵ��Ȳ��Դ���������л�ȡ����������ɺ��߳̽����Żص��̳߳��еȴ���һ�����񣬶��������١����ָ��û����������Դ�����ʲ��������̴߳������ٵĿ�����
 */

class ThreadPool1 {
  using ushort = unsigned short;
  using Task = std::function<void()>;
  ushort thread_size;                    // �����̸߳���
  std::vector<std::thread> thread_list;  // �������߳�
  std::queue<Task> task_queue;           // �������
  std::mutex task_lock;                  // �������ͬ����
  std::mutex add_thread_lock;            // �̳߳�����ͬ����
  std::condition_variable task_cv;       // ��������
  std::atomic<bool> running;             // �̳߳��Ƿ�ִ��
  std::atomic<int> idel_num;             // �����߳�����
 public:
  explicit ThreadPool1(ushort size = 4)
      : thread_size(size), running(true), idel_num(0) {
    std::cout << "hardware_concurrency:" << std::thread::hardware_concurrency()
              << std::endl;
    addThread(size);
  }
  ~ThreadPool1() {
    running = false;
    task_cv.notify_all();
    for (std::thread& thread : thread_list) {
      if (thread.joinable())
        thread.join();
    }
  }

 public:
  inline int idlCount() { return idel_num; }
  inline int threadCount() { return thread_list.size(); }

  // �ύһ������
  // ����.get()��ȡ����ֵ��ȴ�����ִ����,��ȡ����ֵ
  // �����ַ�������ʵ�ֵ������Ա��
  // һ����ʹ��   std::bind�� commit(std::bind(&Dog::sayHello, &dog));
  // һ������   std::mem_fn�� commit(std::mem_fn(&Dog::sayHello), this)
  template <class F, class... Args>
  auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    if (!running)
      throw std::runtime_error("commit on ThreadPool is stopped.");

    // ���� f �ķ���ֵ����
    using RetType = decltype(f(args...));
    using return_type = typename std::result_of<F(Args...)>::type;
    // typename std::result_of<F(Args...)>::type,

    // �Ѻ�����ڼ�����,���(��)
    auto task = std::make_shared<std::packaged_task<RetType()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<RetType> future = task->get_future();

    {
      std::lock_guard<std::mutex> lock{task_lock};

      task_queue.emplace([task]() { (*task)(); });
    }
    if (idel_num < 1 && thread_list.size() < THREADPOOL_MAX_NUM) {
      addThread(1);
    }

    task_cv.notify_one();

    return future;
  }
  // �ύһ���޲�����, ���޷���ֵ
  template <class F>
  void commit2(F&& task) {
    if (!running) {
      return;
    }

    {
      lock_guard<mutex> lock{mutex_lock};
      task_queue.emplace(std::forward<F>(task));
    }
    if (idel_num < 1 && thread_list.size() < THREADPOOL_MAX_NUM)
      addThread(1);
    task_cv.notify_one();
  }

 private:
  void addThread(ushort size) {
    if (!running)
      throw std::runtime_error("Grow on ThreadPool is stopped.");
    std::unique_lock<std::mutex> lockGrow{add_thread_lock};

    for (; thread_list.size() < THREADPOOL_MAX_NUM && size > 0; --size) {
      // �����̺߳���
      thread_list.emplace_back([this] {
        // ��ֹ running==false ʱ��������,��ʱ������п��ܲ�Ϊ��
        while (true) {
          Task task;
          {
            // unique_lock ��� lock_guard �ĺô��ǣ�������ʱ unlock() �� lock()
            std::unique_lock<std::mutex> lock{task_lock};
            task_cv.wait(lock,
                         [this]() { return !running || !task_queue.empty(); });
            if (!running && task_queue.empty()) {
              return;
            }

            idel_num--;
            task = move(task_queue.front());
            task_queue.pop();
          }
          task();
          // ֧���Զ��ͷſ����߳�,�����ֵ������������߳�
          if (idel_num > 0 && thread_list.size() > idel_num) {
            return;
          }

          {
            std::unique_lock<std::mutex> lock{task_lock};
            idel_num++;
          }
        }
      });

      {
        std::unique_lock<std::mutex> lock{task_lock};
        idel_num++;
      }
    }
  }
};
}  // namespace ThreadUsage