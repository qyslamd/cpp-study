#pragma once
#include <iostream>
#include <string>
#include <functional>

namespace op {
struct Question {
  std::string desc;
  std::string zh_CN_desc;
  std::function<void()> answerFunc;
};

class Category {
 public:
  Category(const std::string &desc, const std::vector<Question>& ops);

  void addQuestion(const Question& op);
  void addGoBackOp();
  void execute();
  void quit();

  private:
  std::string op2Str(int cmd, const Question& op);
 private:
  std::string title;
  bool running;
  std::vector<Question> operations;
};
}  // namespace op