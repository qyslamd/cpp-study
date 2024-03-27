#pragma once

#include <string>
#include <iostream>
#include <memory>

namespace factory_method_demo {
/// <summary>
/// Product
/// </summary>
struct Product {
  virtual std::string someOperations() const = 0;
};

struct ConcreteProduct1 : Product {
  std::string someOperations() const override { return "I'm product 1"; }
};

struct ConcreteProduct2 : Product {
  std::string someOperations() const override { return "I'm product 2"; }
};

/// <summary>
/// Factory
/// </summary>
struct Creator {
  virtual std::shared_ptr<Product> factoryMethod() const = 0;
  std::string creatorOperations() const {
    auto product = factoryMethod();
    std::string result =
        "Creator: The same creator's code has just worked with:" +
        product->someOperations();
    return result;
  }
};

struct ConcreteCreator1 : Creator {
  std::shared_ptr<Product> factoryMethod() const override {
    return std::make_shared<ConcreteProduct1>();
  }
};

struct ConcreteCreator2 : Creator {
  std::shared_ptr<Product> factoryMethod() const override {
    return std::make_shared<ConcreteProduct2>();
  }
};

/// <summary>
/// Client
/// </summary>
struct Client {
  void operator()(Creator& creator) {
    std::cout
        << "Client: I'm not ware of the creator's class, but it works fine."
        << std::endl;
    std::cout << creator.creatorOperations() << std::endl;
  }
};

/// <summary>
/// Application
/// </summary>
struct App {
  static void execute() {
    Client client;
    std::cout << "App: launched with ConcreteCreator1." << std::endl;
    std::shared_ptr<Creator> creator1 = std::make_shared<ConcreteCreator1>();
    client(*(creator1.get()));

    std::cout << std::endl;
    std::cout << "App: launched with ConcreteCreator2." << std::endl;
    std::shared_ptr<Creator> creator2 = std::make_shared<ConcreteCreator2>();
    client(*(creator2.get()));

    std::cout << std::endl;
  }
};
}  // namespace factory_method_demo