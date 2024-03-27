#include <iostream>
#include <sstream>
#include <string_view>

#include "utils.h"
#include "basic_and_classic/BasicAndClassic.h"
#include "thread_usage/ThreadUsage.hpp"
#include "design_pattern/DesignPattern.h"

int main(int argc, char* argv[]) {
  using namespace std;
  cout << "*************** Choose a category ***************"
       << endl;
  std::vector<op::Question> ops{
      {"Basic and classic", "经典和基础", basic_and_classic::execute},
      {"Pointer", "指针相关", nullptr},
      {"Thread", "线程相关", thread_usage::execute},
      {"Design Patterns", "设计模式", design_patterns::execute}};
  op::Category factory("Choose a category:", ops);
  factory.execute();
  return 0;
}
