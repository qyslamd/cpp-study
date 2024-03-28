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
      {"What's SOLID principles?", "���ģʽ�����ԭ����ʲô��",
       SOLID::description},
      {"Creational patterns", "������ģʽ", CreationalPatterns::showCategory}};
  op::Category factory("����һ�����֣�ѡ�����ģʽ��ص�֪ʶ�㲢ִ������", ops);
  factory.addGoBackOp();
  factory.execute();
}

void design_patterns::SOLID::description() {
  std::cout << "ʲô�����ģʽ��SOLIDԭ�򣿷ֱ�����Щ��" << std::endl;
  std::cout << "S:" + SRP();
  std::cout << "O:" + OCP();
  std::cout << "L:" + LSP();
  std::cout << "I:" + ISP();
  std::cout << "D:" + ISP();
  std::cout << "" << std::endl;
}

std::string design_patterns::SOLID::SRP() {
  std::stringstream ss;
  ss << "\t��һְ��ԭ��(Single Responsibility Principle)" << std::endl;
  ss << "\tһ�������ģ��Ӧ������ֻ��һ���ı��ԭ��(A class should only have a "
        "single responsibility.)"
     << std::endl;

  return ss.str();
}

std::string design_patterns::SOLID::OCP() {
  std::stringstream ss;
  ss << "\t����ԭ��(Open-Closed Principle)" << std::endl;
  ss << "\t����еĶ����࣬ģ�飬�����ȵȣ�Ӧ�ö�����չ�ǿ��ŵģ����Ƕ����޸�"
        "�Ƿ�յġ�(Entities should be open for extension but closed for "
        "modification.)"
     << std::endl;

  return ss.str();
}

std::string design_patterns::SOLID::LSP() {
  std::stringstream ss;
  ss << "\t�����滻ԭ��(Liskov Substitution Principle)" << std::endl;
  ss << "\t�κλ�����Գ��ֵĵط�������һ�����Գ��֡�(Objects should be "
        "replaceable with instances of their subtypes without altering program "
        "correctness.)"
     << std::endl;

  return ss.str();
}

std::string design_patterns::SOLID::ISP() {
  std::stringstream ss;
  ss << "\t�ӿڸ���ԭ��(Interface Segregation Principle)" << std::endl;
  ss << "\t�ͻ��˲�Ӧ������������Ҫ�Ľӿڡ�һ�������һ���������Ӧ�ý�������С"
        "�Ľӿ���(Many client-specific interfaces better than one "
        "general-purpose interface.)"
     << std::endl;

  return ss.str();
}

std::string design_patterns::SOLID::DI() {
  std::stringstream ss;
  ss << "\t��������ԭ��(Dependency Inversion/Injection)" << std::endl;
  ss << "\t����Ҫ�����ڳ���ӿڣ���Ҫ�����ھ���ʵ�֡�(Dependencies should be "
        "abstract rather than concrete.)"
     << std::endl;

  return ss.str();
}

auto design_patterns::CreationalPatterns::showCategory() -> void {
  std::vector<op::Question> ops{
      {"[Creational Patterns] --- Asbtract Factory", "������ģʽ-���󹤳�",
       abstract_factory_demo::App::execute},
      {"[Creational Patterns] --- Factory Method", "������ģʽ-��������",
       factory_method_demo::App::execute},
      {"[Creational Patterns] --- Builder", "������ģʽ-������ģʽ",
       builder_demo::App::execute},
      {"[Creational Patterns] --- Singleton", "������ģʽ-����ģʽ",
       singleton_demo::App::execute}};
  op::Category category("����һ�����֣�ѡ�����ģʽ��ص�֪ʶ�㲢ִ������", ops);
  category.addGoBackOp();
  category.execute();
}
