#pragma once
/*
* C/C++ 基础面试题，对于应届生来说最常见的问题
*/

#include <string>
#include <iostream>

namespace BasicAndClassic {
enum class Category : char {
  Return = 0,
  MemDistribution,
};
static std::string CateToString(Category cate, const std::string& delim) {
  auto value = std::underlying_type<Category>::type(cate);
  auto result = std::to_string(value) + delim;
  switch (cate) {
    case Category::Return:
      result += "Return";
      break;
    case Category::MemDistribution:
      result += "BasicAndClassic";
      break;
    default:
      break;
  }
  return result;
}

static std::istream& operator>>(std::istream& in, Category& cate) {
  int value;
  in >> value;
  cate = static_cast<Category>(value);
  return in;
}

static std::ostream& operator<<(std::ostream& out, const Category cate) {
  out << CateToString(cate, "");
  return out;
}

void doQuestion(int argc, char* argv[]);

void execute(Category cate);

struct Memory {
  static void desc();
};

}  // namespace BasicAndClassic
