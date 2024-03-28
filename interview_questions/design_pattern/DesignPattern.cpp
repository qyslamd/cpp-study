#include "DesignPattern.h"
#include "../utils.h"

#include <vector>
#include <sstream>

#include "creational_patterns/abstract_factory.hpp"
#include "creational_patterns/factory_method.hpp"
#include "creational_patterns/builder.hpp"
#include "creational_patterns/singleton.hpp"

void design_patterns::execute() {
  std::vector<op::Question> ops{
      {"What's SOLID principles?", "设计模式的五大原则是什么？",
       SOLID::description},
      {"Creational patterns", "创建型模式", CreationalPatterns::showCategory}};
  op::Category factory("输入一个数字，选择设计模式相关的知识点并执行它：", ops);
  factory.addGoBackOp();
  factory.execute();
}

void design_patterns::SOLID::description() {
  std::cout << "什么是设计模式的SOLID原则？分别有哪些？" << std::endl;
  std::cout << "S:" + SRP();
  std::cout << "O:" + OCP();
  std::cout << "L:" + LSP();
  std::cout << "I:" + ISP();
  std::cout << "D:" + ISP();
  std::cout << "" << std::endl;
}

std::string design_patterns::SOLID::SRP() {
  std::stringstream ss;
  ss << "\t单一职责原则(Single Responsibility Principle)" << std::endl;
  ss << "\t一个类或者模块应该有且只有一个改变的原因。(A class should only have a "
        "single responsibility.)"
     << std::endl;

  return ss.str();
}

std::string design_patterns::SOLID::OCP() {
  std::stringstream ss;
  ss << "\t开闭原则(Open-Closed Principle)" << std::endl;
  ss << "\t软件中的对象（类，模块，函数等等）应该对于扩展是开放的，但是对于修改"
        "是封闭的。(Entities should be open for extension but closed for "
        "modification.)"
     << std::endl;

  return ss.str();
}

std::string design_patterns::SOLID::LSP() {
  std::stringstream ss;
  ss << "\t里氏替换原则(Liskov Substitution Principle)" << std::endl;
  ss << "\t任何基类可以出现的地方，子类一定可以出现。(Objects should be "
        "replaceable with instances of their subtypes without altering program "
        "correctness.)"
     << std::endl;

  return ss.str();
}

std::string design_patterns::SOLID::ISP() {
  std::stringstream ss;
  ss << "\t接口隔离原则(Interface Segregation Principle)" << std::endl;
  ss << "\t客户端不应该依赖它不需要的接口。一个类对另一个类的依赖应该建立在最小"
        "的接口上(Many client-specific interfaces better than one "
        "general-purpose interface.)"
     << std::endl;

  return ss.str();
}

std::string design_patterns::SOLID::DI() {
  std::stringstream ss;
  ss << "\t依赖倒置原则(Dependency Inversion/Injection)" << std::endl;
  ss << "\t程序要依赖于抽象接口，不要依赖于具体实现。(Dependencies should be "
        "abstract rather than concrete.)"
     << std::endl;

  return ss.str();
}

auto design_patterns::CreationalPatterns::showCategory() -> void {
  std::vector<op::Question> ops{
      {"[Creational Patterns] --- Asbtract Factory", "创建型模式-抽象工厂",
       abstract_factory_demo::App::execute},
      {"[Creational Patterns] --- Factory Method", "创建型模式-工厂方法",
       factory_method_demo::App::execute},
      {"[Creational Patterns] --- Builder", "创建型模式-生成器模式",
       builder_demo::App::execute},
      {"[Creational Patterns] --- Singleton", "创建型模式-单例模式",
       singleton_demo::App::execute}};
  op::Category category("输入一个数字，选择设计模式相关的知识点并执行它：", ops);
  category.addGoBackOp();
  category.execute();
}
