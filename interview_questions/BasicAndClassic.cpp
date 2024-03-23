#ifdef _WINDOWS
#include<Windows.h>
#endif
#include "BasicAndClassic.h"
#include <sstream>
#include <iostream>

using namespace std;

void BasicAndClassic::execute() {
  std::vector<op::Question> ops{
      {"MemoryDistribute", "C/C++内存分布", Memory::memDist},
      {"malloc() and operator new", "malloc和new的区别", Memory::mallocNewDiff},
      {"The 'static' keyword", "描述下static关键字的作用", StaticKeyword()},
      {"What's Rvalue reference in cpp11?", "在C++11中什么叫做右值引用？", CppCopyAssignDestoy::lRef_rRef}};
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

void BasicAndClassic::StaticKeyword::operator()() {
  std::cout << "Q:static关键字在C++中有哪些用法？" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif  // _WINDOWS

  std::stringstream ss;
  ss << "A:" << std::endl;
  ss << "1. 修饰全局变量" << std::endl;
  ss << "\tstatic 修饰的全局变量表示只可在文件内可见" << std::endl;
  ss << "2. 修饰局部变量" << std::endl;
  ss << "\t当static修饰局部变量时，该变量只在函数内部可见，且生命周期和应用一样"
        "长。且只会被定义一次。"
     << std::endl;
  ss << "3. 修饰类的成员变量" << std::endl;
  ss << "\t修饰类的成员变量的时候，会受到public "
        "protected和private的影响。该变量属于类本身，和类的对象无关。使用类名::"
        "变量名访问。且申明和定义需要分开。"
     << std::endl;
  ss << "4. 修饰普通函数" << std::endl;
  ss << "\t修饰函数表示隐藏。可访问性限定为文件内部" << std::endl;
  ss << "5. 修饰类的成员函数" << std::endl;
  ss << "\t类似于修饰类的成员变量。" << std::endl;
  ss << "!!!特别注意:如果将一个static "
        "全局变量在头文件中申明，那么#"
        "include该头文件的其它地方都能访问到这个变量，但是彼此之间独立"
     << std::endl;
  std::cout << ss.str() << std::endl;
}

void BasicAndClassic::CppCopyAssignDestoy::lRef_rRef() {
  std::cout << "Q:什么叫做右值引用？" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif  // _WINDOWS
  std::stringstream ss;
  ss << "右值引用并非'右'，而是判断表达式是否可以取地址来修改判断是否是右值？" << std::endl;
  ss << "理论上说没有傻逼会直接问这个。但是下边的Demo可以看一眼:" << std::endl;
  ss << R"(
#include <iostream>
#include <string>
int main(){
    std::string s1 = "Test";
    //std::string && r1 = s1; // error,can't bind to lvalue.

    const std::string &r2 = s1 + s1;
    //r2 += "Test"; // error
    std::string && r3 = s1 + s1;
    r3 += "test";   // okay:can be modified through reference to non-const.
    std::cout << r3 << std::endl;
})"
     << std::endl;

  std::cout << ss.str() << std::endl;
}
