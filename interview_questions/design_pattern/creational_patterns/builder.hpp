#pragma once

#include <string>
#include <iostream>
#include <vector>

namespace builder_demo {

struct Product1 {
  std::vector<std::string> parts_;

  void ListParts() const {
    std::cout << "Product parts: ";
    for (size_t i = 0; i < parts_.size(); i++) {
      if (parts_[i] == parts_.back()) {
        std::cout << parts_[i];
      } else {
        std::cout << parts_[i] << ", ";
      }
    }
    std::cout << "\n\n";
  }
};

struct Builder {
  virtual void ProducePartA() const = 0;
  virtual void ProducePartB() const = 0;
  virtual void ProducePartC() const = 0;
};

struct ConcreteBuilder1 : Builder {
 private:
  std::shared_ptr<Product1> product;

  /**
   * A fresh builder instance should contain a blank product object, which is
   * used in further assembly.
   */
 public:
  ConcreteBuilder1() { this->Reset(); }

  void Reset() { this->product.reset(new Product1); }
  /**
   * All production steps work with the same product instance.
   */

  void ProducePartA() const override {
    product->parts_.push_back("PartA1");
  }

  void ProducePartB() const override {
    product->parts_.push_back("PartB1");
  }

  void ProducePartC() const override {
    product->parts_.push_back("PartC1");
  }

  /**
   * Concrete Builders are supposed to provide their own methods for
   * retrieving results. That's because various types of builders may create
   * entirely different products that don't follow the same interface.
   * Therefore, such methods cannot be declared in the base Builder interface
   * (at least in a statically typed programming language). Note that PHP is a
   * dynamically typed language and this method CAN be in the base interface.
   * However, we won't declare it there for the sake of clarity.
   *
   * Usually, after returning the end result to the client, a builder instance
   * is expected to be ready to start producing another product. That's why
   * it's a usual practice to call the reset method at the end of the
   * `getProduct` method body. However, this behavior is not mandatory, and
   * you can make your builders wait for an explicit reset call from the
   * client code before disposing of the previous result.
   */

  std::shared_ptr<Product1> GetProduct() {
    auto result =  this->product;
    this->Reset();
    return result;
  }
};

/**
 * The Director is only responsible for executing the building steps in a
 * particular sequence. It is helpful when producing products according to a
 * specific order or configuration. Strictly speaking, the Director class is
 * optional, since the client can control builders directly.
 */
struct Director {
 private:
  std::shared_ptr<Builder> builder;
  /**
   * The Director works with any builder instance that the client code passes
   * to it. This way, the client code may alter the final type of the newly
   * assembled product.
   */

 public:
  void set_builder(std::shared_ptr<Builder> builder) {
    this->builder = builder;
  }

  /**
   * The Director can construct several product variations using the same
   * building steps.
   */
  void BuildMinimalViableProduct() { this->builder->ProducePartA(); }

  void BuildFullFeaturedProduct() {
    this->builder->ProducePartA();
    this->builder->ProducePartB();
    this->builder->ProducePartC();
  }
};
/**
 * The client code creates a builder object, passes it to the director and then
 * initiates the construction process. The end result is retrieved from the
 * builder object.
 */
/**
 * I used raw pointers for simplicity however you may prefer to use smart
 * pointers here
 */

struct Client {
  void operator()(Director& director) {
    std::shared_ptr<ConcreteBuilder1> builder(new ConcreteBuilder1);
    director.set_builder(builder);
    std::cout << "Standard basic product:\n";
    director.BuildMinimalViableProduct();

    std::shared_ptr<Product1> p = builder->GetProduct();
    p->ListParts();

    std::cout << "Standard full featured product:\n";
    director.BuildFullFeaturedProduct();

    p = builder->GetProduct();
    p->ListParts();

    // Remember, the Builder pattern can be used without a Director class.
    std::cout << "Custom product:\n";
    builder->ProducePartA();
    builder->ProducePartC();
    p = builder->GetProduct();
    p->ListParts();
  }
};

struct App {
  static void execute() {
    Client client;
    Director* director = new Director();
    client(*director);
    delete director;
  }
};
}  // namespace builder_demo