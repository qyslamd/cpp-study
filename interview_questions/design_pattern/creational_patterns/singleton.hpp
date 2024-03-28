#pragma once

#include <string>
#include <iostream>

namespace singleton_demo {

class Singleton {
  std ::string value_;
  Singleton(const std::string& value) : value_(value) {}

 public:
  static Singleton& getInstance(const std::string& value) {
    static Singleton instance(value);
    return instance;
  }
};

struct Client {
    void operator()() {

  }
};

struct App {
  static auto execute() -> void { std::cout << std::endl; }
};
}  // namespace singleton_demo