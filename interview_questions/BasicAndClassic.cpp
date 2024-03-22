#include "BasicAndClassic.h"
#include <sstream>
#include <iostream>
#include <cstdio>

using namespace std;
namespace BasicAndClassic {

void BasicAndClassic::doQuestion(int argc, char* argv[]) {
  while (true) {
    Category cate;
    cout << "Choose your difficulty:" << endl
         << "\t" << CateToString(Category::Return, ": ") << endl
         << "\t" << CateToString(Category::MemDistribution, ": ") << endl;
    cin >> cate;
    cout << "You choosed:" << cate << endl;
    if (cate == Category::Return) {
      cout << "Function will return" << endl;
      return;
    }
    execute(cate);
  }
}

void BasicAndClassic::execute(Category cate) {
  switch (cate) {
    case BasicAndClassic::Category::MemDistribution:
      Memory::desc();
      break;
    default:
      break;
  }
}

void Memory::desc() {
  std::cout << "Q:在C/C++中，内存分配有哪些类型？" << std::endl;
  getchar();
  std::stringstream ss;
  ss << "A:" << std::endl;
  ss << "1、[堆]" << std::endl;
  ss << "\t 指针。使用malloc或者new分配，由程序员负责释放其内存" << std::endl;
  ss << "2、[栈]" << std::endl;
  ss << "\t "
        "局部变量或者函数参数。由编译器负责分配和释放，栈的空间有限，如果在栈"
        "上申请太多内存，有可能导致栈溢出"
     << std::endl;
  ss << "3、[全局、静态]" << std::endl;
  ss << "\t 全局变量和静态(static)变量。由编译器负责分配和释放。" << std::endl;
  ss << "4、[常量存储区]" << std::endl;
  ss << "\t 存储常量和字面值变量。由编译器负责分配和释放。" << std::endl;
  ss << "5、[程序代码区域]" << std::endl;
  ss << "\t 存放程序的二进制代码，由编译器分配和释放。" << std::endl;

  std::cout << ss.str() << std::endl;
}
}  // namespace BasicAndClassic