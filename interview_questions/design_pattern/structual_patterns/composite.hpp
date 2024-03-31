#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

namespace composite_demo {
/*
 * ���ģʽ�ʺ�ʹ�ó�����
 * 1.�����Ҫʵ�����ζ���ṹ������ʹ�����ģʽ
 *	���ģʽΪ���ṩ�����ֹ������ӿڵĻ���Ԫ�����ͣ���Ҷ�ڵ�͸��������������п��԰���Ҷ�ڵ��������������ʹ����Ŀ��Թ�����״Ƕ�׵ݹ����ṹ
 * 2.�����ϣ���ͻ��˴�������ͬ��ʽ����򵥺͸���Ԫ�أ�����ʹ�ø�ģʽ��
 */

/// <summary>
///
/// </summary>
struct Graphics {
  virtual void move(int x, int y) = 0;
  virtual void draw() = 0;
};

struct Dot : Graphics {
  Dot(int x, int y) : x(x), y(y) {}

  void move(int x, int y) override {
    this->x += x;
    this->y += y;
  }
  void draw() override {
    std::cout << "Dot draw: x at:" << x << ", y at:" << y << std::endl;
  }

 private:
  int x;
  int y;
};

struct Circle : Graphics {
  Circle(int x, int y, int radius) : x(x), y(y), radius(radius) {}
  void move(int x, int y) override {
    this->x += x;
    this->y += y;
  }
  void draw() override {
    std::cout << "Circle draw: x at:" << x << ", y at:" << y
              << ", radius is:" << radius << std::endl;
  }

 private:
  int radius;
  int x;
  int y;
};

struct CompoundGraphics : Graphics {
  void add(std::shared_ptr<Graphics> child) {
    if (!std::any_of(children.begin(), children.end(),
                     [child](decltype(child) item) { return child == item; })) {
      this->add(child);
    }
  }

  void remove(std::shared_ptr<Graphics> child) {
    children.erase(
        std::remove_if(children.begin(), children.end(),
                       [child](decltype(child) item) { return item == child; }),
        children.end());
  }

  void move(int x, int y) override {
    std::for_each(
        children.begin(), children.end(),
        [x, y](std::shared_ptr<Graphics> child) { child->move(x, y); });
  }

  void draw() override {
    std::for_each(children.begin(), children.end(),
                  [](std::shared_ptr<Graphics> child) { child->draw(); });
  }

 private:
  std::vector<std::shared_ptr<Graphics>> children;
};

struct Client {
  void load() {
    all = std::make_shared<CompoundGraphics>();
    all->add(std::make_shared<Dot>(2, 3));
    all->add(std::make_shared<Circle>(2, 3, 4));
  }

  void groupSleceted(std::vector<std::shared_ptr<Graphics>> components) {
    std::shared_ptr<CompoundGraphics> group(new CompoundGraphics);
    for (auto item : components) {
      group->add(item);
      all->remove(item);
    }
    all->add(group);
    all->draw();
  }

 private:
  std::shared_ptr<CompoundGraphics> all;
};

struct App {
  static auto execute() -> void {
    Client client;
    client.load();

    std::vector<std::shared_ptr<Graphics>> conps{std::make_shared<Dot>(4, 8)};
    client.groupSleceted(conps);
  }
};
}  // namespace composite_demo