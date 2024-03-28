#pragma once 

#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>

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
  virtual void wangwang() const = 0;
};

struct Corgi : Dog {
  Corgi(const std::string& name) : name(name) {}
  Corgi(const Corgi& other) { name = other.name; }

  std::shared_ptr<Dog> clone() override { return std::make_shared<Corgi>(*this); }

  void wangwang() const override {
    std::cout << "\t" << name << ": wangwang!" << std::endl;
  }

 private:
  std::string name;
};

/// <summary>
/// Client 1
/// </summary>
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

/// <summary>
/// 带一个注册类实现原型模式
/// </summary>
struct Shape {
  virtual ~Shape() {}
  virtual std::shared_ptr<Shape> clone() = 0;
  virtual int getid() const = 0;
  virtual std::string getType() const = 0;
};

struct Circle : Shape {
  Circle(const std::string& type, int id) : type(type), id(id) {}

  Circle(const Circle& other) {
    type = other.type;
    id = other.id;
  }
  std::shared_ptr<Shape> clone() override {
    return std::make_shared<Circle>(*this);
  }
  int getid() const override { return id; }
  std::string getType() const override { return type; }

 private:
  std::string type;
  int id;
};

struct Rectangle : Shape {
  Rectangle(const std::string& type, int id) : type(type), id(id) {}
  Rectangle(const Rectangle& other) {
    type = other.type;
    id = other.id;
  }
  std::shared_ptr<Shape> clone() override {
    return std::make_shared<Rectangle>(*this);
  }
  int getid() const override { return id; }
  std::string getType() const override { return type; }

 private:
  std::string type;
  int id;
};

struct Square : Shape {
  Square(const std::string& type, int id) : type(type), id(id) {}
  Square(const Square& other) {
    type = other.type;
    id = other.id;
  }
  std::shared_ptr<Shape> clone() override {
    return std::make_shared<Square>(*this);
  }
  int getid() const override { return id; }
  std::string getType() const override { return type; }

 private:
  std::string type;
  int id;
};

struct ProtoFactory {
  ProtoFactory() {
    std::shared_ptr<Shape> circle = std::make_shared<Circle>("圆", 1);
    shapeMap.emplace(circle->getType(), circle);
    decltype(circle) rectangle = std::make_shared<Rectangle>("矩形", 2);
    shapeMap.emplace(rectangle->getType(), rectangle);
    decltype(circle) square = std::make_shared<Square>("正方形", 3);
    shapeMap.emplace(square->getType(), square);
  }

  std::shared_ptr<Shape> getShape(const std::string& type) {
    if (auto const& shape = shapeMap[type]) {
      return shape->clone();
    }
    return nullptr;
  }

 private:
  std::unordered_map<std::string, std::shared_ptr<Shape>> shapeMap;
};

/// <summary>
/// Client 2
/// </summary>
struct Client2 {
  void operator()() {
    ProtoFactory factory;
    auto shape1 = factory.getShape("圆");
    std::cout << shape1->getid() << " : " << shape1->getType() << std::endl;
    auto shape2 = factory.getShape("矩形");
    std::cout << shape2->getid() << " : " << shape2->getType() << std::endl;
    auto shape3 = factory.getShape("正方形");
    std::cout << shape3->getid() << " : " << shape3->getType() << std::endl;
  }
};


struct App {
  static void execute() {
    Client1 client1;
    client1();

     Client2 client2;
     client2();
  }
};
}  // namespace prototype_demo