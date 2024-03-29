#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <algorithm>

namespace adapter_demo {
/// <summary>
/// 类适配器
/// </summary>
struct UsbDisck {
 public:
  virtual ~UsbDisck(){};
  virtual void connectDevice() {
    std::cout << "connect to use port." << std::endl;
  };
};

struct TypeCInterface {
  virtual ~TypeCInterface() {}
  void connectDevice() { std::cout << "connect Type-C port." << std::endl; }
};

struct TypeC2UsbAdapter : UsbDisck, TypeCInterface {
  void connectDevice() override { TypeCInterface::connectDevice(); }
};

struct ClassAdapterClient {
  void operator()(std::shared_ptr<UsbDisck> target) { target->connectDevice(); }
};

/// <summary>
/// 对象适配器
/// </summary>
struct Target {
  virtual ~Target() {}
  virtual std::string request() const {
    return "Target: the default target's behavior. ";
  }
};

struct Adaptee {
  std::string specificRequest() const { return "Spacial behavior of adaptee."; }
};

struct Adapter : Target {
  Adapter(std::shared_ptr<Adaptee> adaptee) : adaptee(adaptee) {}
  std::string request() const override {
    std::string to_reverse = adaptee->specificRequest();
    std::reverse(to_reverse.begin(), to_reverse.end());
    return "Adapter:(Translated): " + to_reverse;
  }

 private:
  std::shared_ptr<Adaptee> adaptee;
};

struct ObjectAdapterClient {
  void operator()(std::shared_ptr<Target> target) {
    std::cout << target->request();
  }
};

struct App {
  static void execute() {
    // 类适配器客户端代码
    ClassAdapterClient client0;
    std::shared_ptr<UsbDisck> usb_adapter(new TypeC2UsbAdapter);
    client0(usb_adapter);

    std::cout << std::endl;

    // 对象适配器客户端代码
    ObjectAdapterClient client;
    client(std::make_shared<Target>());
    std::shared_ptr<Adaptee> adaptee(new Adaptee);
    std::shared_ptr<Adapter> adapter(new Adapter(adaptee));
    client(adapter);
    std::cout << std::endl;
  }
};
}  // namespace adapter_demo