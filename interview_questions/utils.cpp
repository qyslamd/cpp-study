#include "utils.h"

namespace op {
Category::Category(const std::string& title,
                     const std::vector<Question>& ops)
    : title(title), running(true), operations(ops) {
  operations.insert(
      operations.begin(),
      Question{"Quit App", "�˳�Ӧ��", std::bind(exit, 0)});
}

void Category::addQuestion(const Question& op) {
  operations.push_back(op);
}

void Category::addGoBackOp() {
  Question op{"Go Back", "������һ��", std::bind(&Category::quit, this)};
  operations.empty() ? operations.push_back(op)
                     : operations.insert(operations.begin() + 1, op);
}

std::string Category::op2Str(int cmd, const Question& op) {
  return std::to_string(cmd) + ": " + op.desc + "(" + op.zh_CN_desc + ")";
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
      if (auto const& func = operations.at(type).opFunc) {
        func();
      }
    }
  }
}

void Category::quit() {
  running = false;
}
}  // namespace op