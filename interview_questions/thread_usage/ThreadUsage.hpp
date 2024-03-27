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
  // 上边的学废了，可以开始写一个线程池了。
  static auto thread_pool_demo() -> void;
};


/*
 * 使用C++11实现一个线程池的步骤及思路整理：
 * 1.一个管理多个线程的线程队列 thread_list
 * 2.一个管理任务的任务队列 task_list
 * 3.添加任务到任务队列 commit_task()
 * 4.线程队列中的线程会按照预定策略（例如FIFO）从队列中取出任务执行，一旦没有任务，休眠自身，等待有任务到来时唤醒。
 * 5.线程执行任务时，会遵循线程池的调度策略从任务队列中获取任务。任务完成后，线程将被放回到线程池中等待下一个任务，而不是销毁。这种复用机制提高了资源利用率并降低了线程创建销毁的开销。
 */

class ThreadPool1 {
  using ushort = unsigned short;
  using Task = std::function<void()>;
  ushort thread_size;                    // 启动线程个数
  std::vector<std::thread> thread_list;  // 已启动线程
  std::queue<Task> task_queue;           // 任务队列
  std::mutex task_lock;                  // 任务队列同步锁
  std::mutex add_thread_lock;            // 线程池增长同步锁
  std::condition_variable task_cv;       // 条件阻塞
  std::atomic<bool> running;             // 线程池是否执行
  std::atomic<int> idel_num;             // 空闲线程数量
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

  // 提交一个任务
  // 调用.get()获取返回值会等待任务执行完,获取返回值
  // 有两种方法可以实现调用类成员，
  // 一种是使用   std::bind： commit(std::bind(&Dog::sayHello, &dog));
  // 一种是用   std::mem_fn： commit(std::mem_fn(&Dog::sayHello), this)
  template <class F, class... Args>
  auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    if (!running)
      throw std::runtime_error("commit on ThreadPool is stopped.");

    // 函数 f 的返回值类型
    using RetType = decltype(f(args...));
    using return_type = typename std::result_of<F(Args...)>::type;
    // typename std::result_of<F(Args...)>::type,

    // 把函数入口及参数,打包(绑定)
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
  // 提交一个无参任务, 且无返回值
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
      // 工作线程函数
      thread_list.emplace_back([this] {
        // 防止 running==false 时立即结束,此时任务队列可能不为空
        while (true) {
          Task task;
          {
            // unique_lock 相比 lock_guard 的好处是：可以随时 unlock() 和 lock()
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
          // 支持自动释放空闲线程,避免峰值过后大量空闲线程
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