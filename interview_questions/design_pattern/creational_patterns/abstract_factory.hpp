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

namespace design_patterns::creational_patterns {

/// <summary>
/// Abstract Product A
/// </summary>
class AbstractProductA {
 public:
  AbstractProductA() = default;
  virtual ~AbstractProductA() {}
  virtual std::string ding() const = 0;
};

class ConcreteProductA1 : public AbstractProductA {
 public:
  ~ConcreteProductA1() override {}
  std::string ding() const override { return "A1::ding()"; }
};

class ConcreteProductA2 : public AbstractProductA {
 public:
  ~ConcreteProductA2() override {}
  std::string ding() const override { return "A2::ding()"; }
};

/// <summary>
/// Abstract Product B
/// </summary>
class AbstractProductB {
 public:
  AbstractProductB() = default;
  virtual ~AbstractProductB() {}
  virtual std::string dong() const = 0;
};

class ConcreteProductB1 : public AbstractProductB {
 public:
  ~ConcreteProductB1() override {}
  std::string dong() const override { return "B1::dong()"; }
};

class ConcreteProductB2 : public AbstractProductB {
 public:
  ~ConcreteProductB2() override {}
  std::string dong() const override { return "B2::dong()"; }
};

/// <summary>
/// Abstract Factory
/// </summary>
class AbstractFactory {
 public:
  virtual ~AbstractFactory(){}
  virtual std::shared_ptr<AbstractProductA> CreateProductA() const = 0;
  virtual std::shared_ptr<AbstractProductB> CreateProductB() const = 0;
};

class ConcreteFactory1 : public AbstractFactory {
 public:
  std::shared_ptr<AbstractProductA> CreateProductA() const override {
    return std::make_shared<ConcreteProductA1>();
  }
  std::shared_ptr<AbstractProductB> CreateProductB() const override {
    return std::make_shared<ConcreteProductB1>();
  }
};

class ConcreteFactory2 : public AbstractFactory {
 public:
  std::shared_ptr<AbstractProductA> CreateProductA() const override {
    return std::make_shared<ConcreteProductA2>();
  }
  std::shared_ptr<AbstractProductB> CreateProductB() const override {
    return std::make_shared<ConcreteProductB2>();
  }
};

void client() {
  auto ClientCode = [](const AbstractFactory& factory) {
    const auto product_a = factory.CreateProductA();
    const auto product_b = factory.CreateProductB();
    std::cout << product_a->ding() << "\n";
    std::cout << product_b->dong() << "\n";
  };

  std::cout << "Client: Testing client code with the first factory type:\n";
  std::shared_ptr<AbstractFactory> factory1 =
      std::make_shared<ConcreteFactory1>();
  ClientCode(*factory1);

  std::cout << std::endl;
  std::cout
      << "Client: Testing the same client code with the second factory type:\n";
  std::shared_ptr<AbstractFactory> factory2 =
      std::make_shared<ConcreteFactory2>();
  ClientCode(*factory2);
}

}  // namespace design_patterns::creational_patterns