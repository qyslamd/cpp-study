#pragma once 

#include <string>
#include <iostream>
#include <memory>

namespace prototype_demo {
/// <summary>
/// 简单的原型模式，避调用抽象类中的clone，使得对象可以直接通过克隆来创建对象。
///     优点1：提高性能
///     优点3：避免使用构造函数
///     优点3：同步对象的状态
/// </summary>
struct Dog {
  virtual ~Dog() {}
  virtual std::shared_ptr<Dog> clone() = 0;
  virtual std::string wangwang() const = 0;
};

struct Corgi : Dog {
  Corgi(const std::string& name) :name(name) {}
  Corgi(const Corgi& other) { name = other.name; }

  std::shared_ptr<Dog> clone() override { return std::make_shared<Dog>(*this); }

  std::string wangwang() const override {
    std::cout << "\t" << name << ": wangwang!" << std::endl;
  }
  private:
  std::string name;
};

struct Client1 {
  void operator()() {
    std::shared_ptr<Dog> dog1 = std::make_shared<Corgi>("YiYi");
    auto dog2 = dog1->clone();
    auto dog3 = dog2->clone();

    dog1->wangwang();
    dog2->wangwang();
    dog3->wangwang();
  }
};


struct Shape {
  virtual ~Shape() {}
  virtual std::shared_ptr<Shape> clone() = 0;
  virtual int getid() = 0;
  virtual std::string getType() = 0;

 protected:
  std::string type;
};

struct Circle {
  Circle(const std::string& type, int id) {}

};

struct App {
  static void execute() {}
};
}