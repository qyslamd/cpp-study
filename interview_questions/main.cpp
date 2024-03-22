#include <iostream>
#include <sstream>
#include <string_view>

#include "utils.h"
#include "BasicAndClassic.h"

int main(int argc, char* argv[]) {
  using namespace std;
  cout << "*************** Welcome to my interview questsions ***************"
       << endl;
  std::vector<op::Question> ops{{"BasicAndClassic", "基础且经典的面试题",
                                  [] {
                                    BasicAndClassic::Memory mem;
                                    mem();
                                  }},
                                 {"Pointer", "指针相关", nullptr}};
  op::Category factory("Choose a category:", ops);
  factory.execute();
  return 0;
}
