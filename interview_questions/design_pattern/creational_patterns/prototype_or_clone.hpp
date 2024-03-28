#pragma once 

#include <string>
#include <iostream>
#include <memory>

namespace prototype_demo {
/// <summary>
/// �򵥵�ԭ��ģʽ���ܵ��ó������е�clone��ʹ�ö������ֱ��ͨ����¡����������
///     �ŵ�1���������
///     �ŵ�3������ʹ�ù��캯��
///     �ŵ�3��ͬ�������״̬
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