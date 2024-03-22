#include <iostream>
#include <sstream>
#include <string_view>

#include "utils.hpp"
#include "BasicAndClassic.h"

namespace Cate{
enum class Category : char {
  Quit = 0,
  BasicAndClassic,  // 基础而且经典的
  Pointer,          // 指针
  ObjectOriented,   // 面向对象
};

static std::string CateToString(Category cate, const std::string & delim) {
  auto value = std::underlying_type<Category>::type(cate);
  auto result = std::to_string(value) + delim;
  switch (cate) {
    case Category::Quit:
      result += "Quit";
      break;
    case Category::BasicAndClassic:
      result += "BasicAndClassic";
      break;
    case Category::Pointer:
      result += "Pointer";
      break;
    case Category::ObjectOriented:
      result += "ObjectOriented";
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
}  // namespace Cate

static void DoQuestions(Cate::Category cate, int argc, char* argv[]);

int main(int argc, char* argv[]) {
  using namespace std;
  using namespace Cate;
  cout
      << "*************** Welcome to my interview questsions ***************"
      <<endl;

  bool recycle = true;
  while (recycle) {
    Category cate;
    cout << "Choose your difficulty:" << endl
         << "\t" << CateToString(Category::Quit, ": ")
         << endl
         << "\t" << CateToString(Category::BasicAndClassic, ": ") << endl
         << "\t" << CateToString(Category::Pointer, ": ") << endl
         << "\t" << CateToString(Category::ObjectOriented, ": ") << endl;
    cin >> cate;
    cout << "You choosed:" << cate << endl;
    if (cate == Category::Quit) {
      recycle = false;
      cout << "Application will quit" << endl;
    }
    DoQuestions(cate, argc, argv);
  }
  return 0;
}

void DoQuestions(Cate::Category cate, int argc, char* argv[]) {
  using namespace Cate;
  switch (cate) {
    case Category::Quit:
      break;
    case Category::BasicAndClassic:
      BasicAndClassic::doQuestion(argc, argv);
      break;
    case Category::Pointer:
      break;
    case Category::ObjectOriented:
      break;
    default:
      break;
  }
}
