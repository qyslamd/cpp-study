#pragma once
#include <string>
#include <iostream>
#include <functional>

namespace op {
struct Question {
  std::string desc;
  std::string zh_CN_desc;
  std::function<void()> answerFunc;
};

class Category {
 public:
  Category(const std::string& desc, const std::vector<Question>& ops);

  void addQuestion(const Question& op);
  void addGoBackOp();
  void execute();
  inline void quit() { running = false; }
 private:
  inline std::string op2Str(int cmd, const Question& op) {
    return std::to_string(cmd) + ": " + op.desc + "(" + op.zh_CN_desc + ")";
  }

 private:
  std::string title;
  bool running;
  std::vector<Question> operations;
};
}  // namespace op