#ifdef _WINDOWS
#include<Windows.h>
#endif
#include "BasicAndClassic.h"
#include <sstream>
#include <iostream>

using namespace std;

void BasicAndClassic::Memory::operator()() {
  std::vector<op::Question> ops{
      {"MemoryDistribute", "C/C++内存分布", [this] { memDist(); }},
      {"malloc() and operator new", "malloc和new的区别",
       [this] { mallocNewDiff(); }}};
  op::Category factory("Choose a question:", ops);
  factory.addGoBackOp();
  factory.execute();
}

void BasicAndClassic::Memory::memDist() {
  std::cout << "Q:在C/C++中，内存分配有哪些类型？" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif  // _WINDOWS

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

void BasicAndClassic::Memory::mallocNewDiff() {
  std::cout << "Q:malloc 和 new 有什么区别？" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif  // _WINDOWS

  std::stringstream ss;
  ss << "A:" << std::endl;
  ss << "malloc 是C语言库函数，new是C++中的关键字，也是一个可以被重载的操作符"
     << std::endl;
  std::cout << ss.str() << std::endl;
}
