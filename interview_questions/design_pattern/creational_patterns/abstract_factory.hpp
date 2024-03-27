#pragma once

#include <string>
#include <iostream>
#include <memory>

/*
* 参考这里发现更多
* 中文版：
* https://refactoringguru.cn/design-patterns/abstract-factory
* 英文版：
* https://refactoring.guru/design-patterns/abstract-factory
*/

namespace abstract_factory_demo {

/// <summary>
/// Abstract Product A
/// </summary>
struct AbstractProductA {
  virtual std::string ding() const = 0;
};

struct ConcreteProductA1 : AbstractProductA {
  std::string ding() const override { return "A1::ding()"; }
};

struct ConcreteProductA2 : AbstractProductA {
  std::string ding() const override { return "A2::ding()"; }
};

/// <summary>
/// Abstract Product B
/// </summary>
struct AbstractProductB {
  virtual std::string dong() const = 0;
};

struct ConcreteProductB1 : AbstractProductB {
  std::string dong() const override { return "B1::dong()"; }
};

struct ConcreteProductB2 : AbstractProductB {
  std::string dong() const override { return "B2::dong()"; }
};

/// <summary>
/// Abstract Factory
/// </summary>
struct AbstractFactory {
  virtual std::shared_ptr<AbstractProductA> CreateProductA() const = 0;
  virtual std::shared_ptr<AbstractProductB> CreateProductB() const = 0;
};

struct ConcreteFactory1 : AbstractFactory {
  std::shared_ptr<AbstractProductA> CreateProductA() const override {
    return std::make_shared<ConcreteProductA1>();
  }
  std::shared_ptr<AbstractProductB> CreateProductB() const override {
    return std::make_shared<ConcreteProductB1>();
  }
};

struct ConcreteFactory2 : AbstractFactory {
  std::shared_ptr<AbstractProductA> CreateProductA() const override {
    return std::make_shared<ConcreteProductA2>();
  }
  std::shared_ptr<AbstractProductB> CreateProductB() const override {
    return std::make_shared<ConcreteProductB2>();
  }
};

struct Client {
  void operator()(AbstractFactory& factory) {
    const auto product_a = factory.CreateProductA();
    const auto product_b = factory.CreateProductB();
    std::cout << product_a->ding() << "\n";
    std::cout << product_b->dong() << "\n";
  }
};

struct App {
  static void execute() {
    Client client;
    std::cout << "Client: Testing client code with the first factory type:\n";
    std::shared_ptr<AbstractFactory> factory1 =
        std::make_shared<ConcreteFactory1>();
    client(*factory1);

    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory "
                 "type:\n";
    std::shared_ptr<AbstractFactory> factory2 =
        std::make_shared<ConcreteFactory2>();
    client(*factory2);

    std::cout << std::endl;
  }
};
}  // namespace abstract_factory_demo