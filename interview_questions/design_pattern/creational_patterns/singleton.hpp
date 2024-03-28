#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

namespace singleton_demo {

class SingletonBase {
 public:
  SingletonBase(const std::string& value) : value(value) {}

  virtual ~SingletonBase() {}
  SingletonBase() = delete;
  SingletonBase(const SingletonBase&) = delete;
  SingletonBase& operator=(const SingletonBase&) = delete;
  SingletonBase(SingletonBase&& other) noexcept = delete;
  SingletonBase& operator=(SingletonBase&& other) noexcept = delete;

  inline std::string getValue() const { return value; }

 private:
  std ::string value;
};

/// <summary>
/// Meyers Singleton
/// </summary>
class MayersSingleton : public SingletonBase {
 public:
  static MayersSingleton& getInstance(const std::string& value) {
    static MayersSingleton instance(value);
    return instance;
  }

 protected:
  MayersSingleton(const std::string& value) : SingletonBase(value) {}
  ~MayersSingleton() {}
  MayersSingleton(const MayersSingleton&) = delete;
  MayersSingleton& operator=(const MayersSingleton&) = delete;
};

/// <summary>
/// Leaky singleton
/// </summary>
class LeakySingleton : public SingletonBase {
 public:
  static LeakySingleton& getInstance(const std::string& value) {
      // 程序结束，等待操作系统回收
    static LeakySingleton* instance = new LeakySingleton(value);
    return *instance;
  }

 private:
  LeakySingleton(const std::string& value) : SingletonBase(value) {}
  ~LeakySingleton() {}
  LeakySingleton(const LeakySingleton&) = delete;
  LeakySingleton& operator=(const LeakySingleton&) = delete;
};

/// <summary>
/// Before C++11,singleton
/// </summary>
class BeforeCpp11Singleton : public SingletonBase {
 public:
  static BeforeCpp11Singleton& getInstance(const std::string& value) {
    if (!instance) {
      std::lock_guard<std::mutex> lock(mutex);
      if (!instance) {
        instance = new BeforeCpp11Singleton(value); // 程序结束，等待操作系统回收了。
      }
    }
    return *instance;
  }

 private:
  static BeforeCpp11Singleton* instance;
  static std::mutex mutex;
 private:
  BeforeCpp11Singleton(const std::string& value) : SingletonBase(value) {}
  ~BeforeCpp11Singleton() {}
  BeforeCpp11Singleton(const BeforeCpp11Singleton&);
  BeforeCpp11Singleton& operator=(const BeforeCpp11Singleton&);
};
BeforeCpp11Singleton* BeforeCpp11Singleton::instance = nullptr;
std::mutex BeforeCpp11Singleton::mutex;

template <typename T>
struct Client {
  void operator()() {
    std::cout << "If you see the same value, then singleton was reused (yay!\n"
              << "If you see different values, then 2 singletons were created "
                 "(booo!!)"
              << std::endl
              << "RESULT: " << std::endl;

    std::thread thread1(std::mem_fn(&Client::threadTest), *this, "Foo");
    std::thread thread2(std::mem_fn(&Client::threadTest), *this, "Bar");
    thread1.join();
    thread2.join();
  }

  void threadTest(const std::string& value) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    auto const & singleton = T::getInstance(value);
    std::cout << "In thread: " << std::this_thread::get_id()
              << " ,value is: " << singleton.getValue() << std::endl;
    std::cout << std::endl;
  }
};

struct App {
  static auto execute() -> void {
    Client<MayersSingleton> client1;
    client1();
    std::cout << std::endl;

    Client<LeakySingleton> client2;
    client2();
    std::cout << std::endl;

    Client<BeforeCpp11Singleton> client3;
    client3();
    std::cout << std::endl;
  }
};
}  // namespace singleton_demo