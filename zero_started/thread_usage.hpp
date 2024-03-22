#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

namespace cpp_study::thread_usage::std_thread {

struct Foo {
  Foo(int num) : num_(num) {}
  void print_add(int i) const { std::cout << num_ + i << '\n'; }
  int num_;
};

void print_num(int i) {
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  std::cout << "Function '" << __FUNCTION__
            << "' runs on:" << std::this_thread::get_id() << std::endl;
  std::cout << "i is : " << i << '\n';
}

struct PrintNum {
  void operator()(int i) const { std::cout << i << '\n'; }
  size_t operator()(const std::string& str) {
    std::cout << str << "\n";
    return str.size();
  }
};

void test_code() {
  std::function<void(int)> f_1 = print_num;
  std::thread thread1(f_1, 42);
  thread1.join();

  std::function<void()> f_1_99 = std::bind(print_num, 99);
  std::thread thread2(f_1_99);
  thread2.join();

  std::function<void(const Foo&, int)> f_2 =
      std::bind(&Foo::print_add, std::placeholders::_1, std::placeholders::_2);
  const Foo foo(314159);
  std::thread thread3(f_2, foo, 1);
  thread3.join();
  std::thread thread4(f_2, 1, 1);
  thread4.join();

  std::function<int(const Foo&)> f_3 = &Foo::num_;
  std::cout << "num_: " << f_3(foo) << std::endl;

  std::function<void(int)> f_4 = PrintNum();
  f_4(18);

  std::function<int(std::string)> f_5 = PrintNum();
  std::cout << "int PrintNum::operator()(const std::string &): " << f_5("hello") << std::endl;
}

}  // namespace cpp_study::thread_usage::std_thread
