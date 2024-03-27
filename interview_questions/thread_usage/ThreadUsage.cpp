#include "ThreadUsage.hpp"
#include "utils.h"

#include <chrono>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <sstream>

void thread_usage::execute() {
  using opList = std::vector<op::Question>;
  opList ops{
      {"std::thread", "std::thread的基础用法",
       BasicThread::thread_demo},
      {"std::mutex", "std::mutext的基本用法",
       BasicThread::mutex_lock_demo},
      {"std::condition_variable", "std::condition_variable用法示例",
       BasicThread::condition_variable_demo},
      {"std::promise", "std::promise的示例用法",
       BasicThread::promise_demo},
      {"std::packaged_task", "std::packaged_task的用法示例",
       BasicThread::packaged_task_demo},
      {"std::async", "std::async的用法示例", BasicThread::async_demo},
      {"std::call_once", "std::call_once的用法示例",
       BasicThread::call_once_demo},
      {"Create a simple thread pool", "使用C++11提供的线程接口以及一些其它的设施，实现一个简单的线程池",
       ThreadAvanced::thread_pool_demo}};
  op::Category factory("线程相关的知识点:", ops);
  factory.addGoBackOp();
  factory.execute();
}

auto thread_usage::BasicThread::thread_demo() -> void {
  std::cout << __FUNCTION__ << "thread id:" << std::this_thread::get_id
            << std::endl;
  std::thread thread1([] {
      using namespace std::chrono_literals;
    std::cout << "thread id:" << std::this_thread::get_id << std::endl;
    std::this_thread::sleep_for(3s);
  });
  thread1.join();
}

namespace mutex_lock_utility {
static std::mutex mutex1;
void testMutex() {
  auto func = [](int n, char f) {
    mutex1.lock();
    for (int i = 0; i < n; i++) {
      std::cout << f;
    }
    std::cout << "\n";
    mutex1.unlock();
  };
  std::thread t1(func, 30, 'S');
  std::thread t2(func, 20, 'B');
  t1.join();
  t2.join();
}

static std::mutex mutex2;
void testTryLock() {
  auto func = [](int n, char f) {
    if (mutex2.try_lock()) {
      for (int i = 0; i < n; i++) {
        std::cout << f;
      }
      std::cout << "\n";
      mutex2.unlock();
    }
  };

  std::thread t1(func, 30, 'N');
  std::thread t2(func, 20, 'B');
  t1.join();
  t2.join();
}

volatile int g_i = 0;
static std::mutex g_i_mutex;
void testLockGuard() {
  auto safe_increament = [](int iterations) {
    const std::lock_guard<std::mutex> lock(g_i_mutex);
    while (iterations-- > 0) {
      g_i = g_i + 1;
    }
    std::cout << "thread #" << std::this_thread::get_id() << " , g_i: " << g_i
              << std::endl;
    // g_i_mutex is automatically released when lock goes out of scope.
  };

  auto unsafe_increment = [](int iterations) {
    while (iterations-- > 0) {
      g_i = g_i + 1;
      // std::cout << "thread #" << std::this_thread::get_id() << ", g_i: " <<
      // g_i
      //           << '\n';
    }
  };

  auto test = [=](const std::string& fun_name, auto fun) {
    g_i = 0;
    std::cout << fun_name << "\n before,g_i: " << g_i << std::endl;
    std::thread th1(fun, 1'000);
    std::thread th2(fun, 1'000);
    th1.join();
    th2.join();
    std::cout << "after: g_i: " << g_i << "\n\n";
  };

  test("safe_increment", safe_increament);
  test("unsafe_increment", unsafe_increment);
}


void testUniqueLock() {
  struct Box {
    explicit Box(int num) : num_things(num) {}
    int num_things;
    std::mutex m;
  };

  auto transfer = [](Box& from, Box& to, int num) {
    std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
    std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);

    std::lock(lock1, lock2);

    from.num_things -= num;
    to.num_things += num;
  };

  Box acc1(100);
  Box acc2(50);

  std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
  std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);
  t1.join();
  t2.join();

  std::cout << "acc1.num_things: " << acc1.num_things << std::endl;
  std::cout << "acc2.num_things: " << acc2.num_things << std::endl;
}

}  // namespace mutex_lock_utility
auto thread_usage::BasicThread::mutex_lock_demo() -> void {
  mutex_lock_utility::testMutex();

  mutex_lock_utility::testTryLock();

  mutex_lock_utility::testLockGuard();

  mutex_lock_utility::testUniqueLock();
}

auto thread_usage::BasicThread::condition_variable_demo() -> void {
  std::mutex m;
  std::string data;
  std::condition_variable cv;
  bool ready = false;
  bool processed = false;

  auto worker_thread = [&]() {
    // wait until caller send data.
    std::unique_lock lk(m);
    cv.wait(lk, [&ready] { return ready; });

    // after the wait, we own the lock
    std::cout << "woking thread is processing data.\n";
    data += "after processing";

    // send data back to caller
    processed = true;
    std::cout << "worker thread signals data processing completed\n";

    // manual unlocking is done before notifying, to void waking up
    // tge waiting thread only to block again (see notify_one for details.)
    lk.unlock();
    cv.notify_one();
  };

  std::thread worker(worker_thread);

  data = "Examle data";

  // Send data back to worker thread.
  {
    std::lock_guard<std::mutex> lk(m);
    ready = true;
    std::cout << "caller signals data ready for processing\n";
    cv.notify_one();
  }

  // wait for the worker.
  {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [&processed] { return processed; });
  }

  std::cout << "Back to the caller, data = " << data << "\n";

  worker.join();
}

auto thread_usage::BasicThread::promise_demo() -> void {
  auto accumulate = [](std::vector<int>::iterator first,
                       std::vector<int>::iterator last,
                       std::promise<int> accumulate_promise) {
    int sum = std::accumulate(first, last, 0);
    accumulate_promise.set_value(sum);
  };

  auto doWork = [](std::promise<void> barrier) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    barrier.set_value();
  };

  std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
  std::promise<int> accumulate_promise;
  std::future<int> accumulate_future = accumulate_promise.get_future();
  std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
                          std::move(accumulate_promise));
  // future::get() will wait until the future has a valid result and retrives
  // it. Calling wait() before get() is not needed. accumulate_future.wait(); //
  // wait for the result
  std::cout << "result=" << accumulate_future.get() << std::endl;
  work_thread.join();  // wait for thread completion.

  // Demonstrate using promise<void> to signal thread between threads.
  std::promise<void> barrier;
  std::future<void> barrier_future = barrier.get_future();
  std::thread net_work_thread(doWork, std::move(barrier));
  barrier_future.wait();
  net_work_thread.join();
}


namespace package_task_utility {
int f(int x, int y) {
  return std::pow(x, y);
}

void task_lambda() {
  // std::packaged_task是一个模板类，重载了operator(),不带参数的，所以调用之后的返回值是通过std::future获取的
  std::packaged_task<int(int, int)> task(
      [](int a, int b) { return std::pow(a, b); });
  std::future<int> result = task.get_future();
  task(2, 5);
  std::cout << "task lambda:\t" << result.get() << std::endl;
}

void task_bind() {
  std::packaged_task<int()> task(std::bind(f, 2, 6));
  std::future<int> result = task.get_future();

  task();

  std::cout << "task_bind:\t" << result.get() << std::endl;
}

void task_thread() {
  std::packaged_task<int(int, int)> task(f);
  std::future<int> result = task.get_future();

  std::thread task_td(std::move(task), 2, 7);
  task_td.join();

  std::cout << "task_thread:\t" << result.get() << std::endl;
}
}  // namespace package_task_utility

auto thread_usage::BasicThread::packaged_task_demo() -> void {
  package_task_utility::task_lambda();
  package_task_utility::task_bind();
  package_task_utility::task_thread();
}


namespace async_utility {
std::mutex m;
struct X {
  void foo(int i, const std::string& str) {
    std::lock_guard<std::mutex> lk(m);
    std::cout << str << ' ' << i << std::endl;
  }
  void bar(const std::string& str) {
    std::lock_guard<std::mutex> lk(m);
    std::cout << str << std::endl;
  }

  int operator()(int i) {
    std::lock_guard<std::mutex> lk(m);
    std::cout << i << std::endl;
    return i += 10;
  }
};
template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end) {
  auto len = end - beg;
  if (len < 1000) {
    return std::accumulate(beg, end, 0);
  }

  RandomIt mid = beg + len / 2;
  auto handle =
      std ::async(std::launch::async, parallel_sum<RandomIt>, mid, end);
  int sum = parallel_sum(beg, mid);

  return sum + handle.get();
}
}  // namespace async_utility

auto thread_usage::BasicThread::async_demo() -> void {
  using namespace async_utility;
  std::vector<int> v(10000, 1);
  std::cout << "The sum is:"
            << parallel_sum<decltype(v.begin())>(v.begin(), v.end())
            << std::endl;
  X x;
  // Call (&x)->foo(42, "hello") with default policy
  auto a1 = std::async(&X::foo, &x, 42, "Hello");

  // Call x.bar("world!") with deffered policy.
  // prints "world!" when a2.get() or a2.wait() is called.
  auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");

  // Call X()(43) with async policy
  // prints "43" concurrently
  auto a3 = std::async(std::launch::async, X(), 43);
  a2.wait();
  std::cout << a3.get() << std::endl;
}


namespace call_once_utility {
std::once_flag flag1, flag2;

void simple_do_once() {
  std::call_once(flag1, []() { std::cout << "Simple example: called once\n"; });
}

auto may_throw_fuction = [](bool do_throw) -> void {
  if (do_throw) {
    std::cout << "Throw: call once will retry\n";
    throw std::exception();
  }
  std::cout << "Did not throw, call_once will not attempt again\n";
};

void do_once(bool do_throw) {
  try {
    std::call_once(flag2, may_throw_fuction, do_throw);
  } catch (...) {
  };
}
}  // namespace call_once_utility

auto thread_usage::BasicThread::call_once_demo() -> void {
  using namespace call_once_utility;
  std::thread st1(simple_do_once);
  std::thread st2(simple_do_once);
  std::thread st3(simple_do_once);
  std::thread st4(simple_do_once);
  st1.join();
  st2.join();
  st3.join();
  st4.join();

  std::thread t1(do_once, true);
  std::thread t2(do_once, true);
  std::thread t3(do_once, false);
  std::thread t4(do_once, true);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
}

namespace thread_pool_utility {
void fun1(int mills) {
  std::cout << "  hello, fun1 !  " << std::this_thread::get_id() << "\n";
  if (mills > 0) {
    std::cout << " ======= fun1 sleep " << mills
              << "  =========  " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(mills));
  }
}

struct gfun {
  int operator()(int n) {
    std::cout << n << "  hello, gfun !  " << std::this_thread::get_id()
              << std::endl;
    return 42;
  }
};

class A {
 public:
  static int Afun(int n = 0) {
    std::cout << n << "  hello, Afun !  " << std::this_thread::get_id()
              << std::endl;
    return n;
  }

  static std::string Bfun(int n, std::string str, char c) {
    std::cout << n << "  hello, Bfun !  " << str.c_str() << "  " << (int)c
              << "  " << std::this_thread::get_id() << std::endl;
    return str;
  }
};

}  // namespace thread_pool_utility

auto thread_usage::ThreadAvanced::thread_pool_demo() -> void {
  using namespace thread_pool_utility;
  try {
    ThreadPool1 executor{50};
    A a;
    auto ff = executor.commit(fun1, 0);
    auto fg = executor.commit(gfun{}, 0);
    auto gg = executor.commit(a.Afun, 9999);
    auto gh = executor.commit(A::Bfun, 9998, "mult args", 123);
    auto fh = executor.commit([]() -> std::string {
      std::cout << "hello, fh !  " << std::this_thread::get_id() << std::endl;
      return "hello,fh ret !";
    });

    std::cout << " =======  sleep ========= " << std::this_thread::get_id()
              << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(900));

    for (int i = 0; i < 50; i++) {
      executor.commit(fun1, i * 100);
    }
    std::cout << " =======  commit all ========= " << std::this_thread::get_id()
              << " idlsize=" << executor.idlCount() << std::endl;

    std::cout << " =======  sleep ========= " << std::this_thread::get_id()
              << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    ff.get();
    std::cout << fg.get() << "  " << fh.get().c_str() << "  "
              << std::this_thread::get_id() << std::endl;

    std::cout << " =======  sleep ========= " << std::this_thread::get_id()
              << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << " =======  fun1,55 ========= " << std::this_thread::get_id()
              << std::endl;
    executor.commit(fun1, 55).get();  // 调用.get()获取返回值会等待线程执行完

    std::cout << "end... " << std::this_thread::get_id() << std::endl;

    ThreadPool1 pool(4);
    std::vector<std::future<int> > results;

    for (int i = 0; i < 8; ++i) {
      results.emplace_back(pool.commit([i] {
        std::cout << "hello " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "world " << i << std::endl;
        return i * i;
      }));
    }
    std::cout << " =======  commit all2 ========= "
              << std::this_thread::get_id() << std::endl;

    for (auto&& result : results) {
      std::cout << result.get() << ' ';
    }
    std::cout << std::endl;
  } catch (std::exception& e) {
    std::cout << "some unhappy happened...  " << std::this_thread::get_id()
              << e.what() << std::endl;
  }
}
