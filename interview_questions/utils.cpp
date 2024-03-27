#include "utils.h"

namespace op {
Category::Category(const std::string& title,
                     const std::vector<Question>& ops)
    : title(title), running(true), operations(ops) {
  operations.insert(
      operations.begin(),
      Question{"Quit App", "退出应用", std::bind(exit, 0)});
}

void Category::addQuestion(const Question& op) {
  operations.push_back(op);
}

void Category::addGoBackOp() {
  Question op{"Go Back", "返回上一级", std::bind(&Category::quit, this)};
  operations.empty() ? operations.push_back(op)
                     : operations.insert(operations.begin() + 1, op);
}

void Category::execute() {
  while (running) {
    std::cout << title << std::endl;
    for (decltype(operations.size()) i = 0; i < operations.size(); i++) {
      std::cout << "\t" + op2Str(i, operations.at(i)) << std::endl;
    }
    int type = 0;
    std::cin >> type;
    if (type < 0) {
      continue;
    }
    if (type < operations.size()) {
      if (auto const& func = operations.at(type).answerFunc) {
        func();
      }
    }
  }
}
}  // namespace op