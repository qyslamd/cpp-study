#ifdef _WINDOWS
#include<Windows.h>
#endif
#include "BasicAndClassic.h"
#include <sstream>
#include <iostream>
#include <memory>

#include "utils.h"

using namespace std;

void basic_and_classic::execute() {
  std::vector<op::Question> ops{
      {"MemoryDistribute", "C/C++内存分布", Memory::memDist},
      {"malloc() and operator new", "malloc和new的区别", Memory::mallocNewDiff},
      {"The 'static' keyword", "描述下static关键字的作用", StaticKeyword()},
      {"What's Rvalue reference in cpp11?", "在C++11中什么叫做右值引用？",
       CppCopyAssignDestoy::lRef_rRef},
      {"What's rules of three/five?", "C++中的3/5法则以及0法则",
       CppCopyAssignDestoy::_3_5_rules},
      {"Describe the explicit type conversion keyword in C++",
       "描述C++中的显式类型转换关键字", CastInCpp::describeCastInCpp},
      {"Write a string class", "自己写一个String类",
       CppCopyAssignDestoy::testMyString}};
  op::Category factory("选择一个基础的问题或者命令，数字代表执行它", ops);
  factory.addGoBackOp();
  factory.execute();
}

void basic_and_classic::Memory::memDist() {
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

void basic_and_classic::Memory::mallocNewDiff() {
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

void basic_and_classic::Memory::smartPointers() {
  std::cout << "这里就简单记录下C++11中提供的智能指针的用法。" << std::endl;

  std::stringstream ss;

  std::cout << ss.str() << std::endl;
}

void basic_and_classic::StaticKeyword::operator()() {
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

void basic_and_classic::CppCopyAssignDestoy::lRef_rRef() {
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

void basic_and_classic::CppCopyAssignDestoy::_3_5_rules() {
  std::cout << "Q：在C++中什么叫做3/5法则？" << std::endl;
  #ifdef _WINDOWS
  system("pause");
  #endif

  std::stringstream ss;
  ss << "A:"
        "在一个类中，有三个基本操作可以控制类的拷贝操作：拷贝构造函数、拷贝赋值"
        "运算符和析构函数。这称之为三法则。在新版的C++"
        "11标准中，引入了右值引用。还可以定义一个移动构造函数和一个移动赋值运算"
        "符。0法则指的是当用到这些操作的时候，如果用户未显式的定义这些操作，那么编译器将自动生成。";
  ss << "下边是一个常见的定义了5个操作的类的示例：" << std::endl;
  ss << R"(
  Foo(const Foo& other) {
    // copy constructor.
    // If you don't write it explicitly, the compiler will automatically create
    // a version that does nothing
    std::cout << "Copy constructor was called!" << std::endl;

    this->size = other.size;

    // shallow copy.
    this->buf = other.buf;

    // deep copy.
    this->buf = new char[other.size];
    memcpy(this->buf, other.buf, other.size);
  }

  Foo& operator=(const Foo& other) {
    // Copy assignment operator.
    std::cout << "Copy assign operator was called!" << std::endl;

    if (this != &other) {
      delete this->buf;
      this->size = other.size;
      this->buf = new char[other.size];
      memcpy(this->buf, other.buf, other.size);
    }

    return *this;
  }

  Foo(Foo&& other) noexcept {
    // Move constructor
    std::cout << "Move constructor was called!" << std::endl;
    this->size = other.size;
    this->buf = other.buf;

    other.size = 0;
    other.buf = nullptr;
  }

  Foo& operator=(Foo&& other) noexcept {
    // Move assignment operator
    std::cout << "Move assignment operator was called!" << std::endl;

    if (this != &other) {
      delete this->buf;
      this->size = other.size;
      this->buf = other.buf;

      other.size = 0;
      other.buf = nullptr;
    }

    return *this;
  }
};
)";
  ss << std::endl;

  std::cout << ss.str() << std::endl;
}

class Foo {
 private:
  size_t size;
  char* buf;

 public:
  Foo() : size(0), buf(new char(size)) {
    // default constructor.
    // If you don't write it explicitly, the compiler will automatically create
    // a version that does nothing
    std::cout << "Default constructor was called!" << std::endl;
  }

  ~Foo() {
    std::cout << "Desctructor." << std::endl;
    delete[] buf;
  }

  Foo(const Foo& other) {
    // copy constructor.
    // If you don't write it explicitly, the compiler will automatically create
    // a version that does nothing
    std::cout << "Copy constructor was called!" << std::endl;

    this->size = other.size;

    // shallow copy.
    this->buf = other.buf;

    // deep copy.
    this->buf = new char[other.size];
    memcpy(this->buf, other.buf, other.size);
  }

  Foo& operator=(const Foo& other) {
    // Copy assignment operator.
    std::cout << "Copy assign operator was called!" << std::endl;

    if (this != &other) {
      delete this->buf;
      this->size = other.size;
      this->buf = new char[other.size];
      memcpy(this->buf, other.buf, other.size);
    }

    return *this;
  }

  Foo(Foo&& other) noexcept {
    // Move constructor
    std::cout << "Move constructor was called!" << std::endl;
    this->size = other.size;
    this->buf = other.buf;

    other.size = 0;
    other.buf = nullptr;
  }

  Foo& operator=(Foo&& other) noexcept {
    // Move assignment operator
    std::cout << "Move assignment operator was called!" << std::endl;

    if (this != &other) {
      delete this->buf;
      this->size = other.size;
      this->buf = other.buf;

      other.size = 0;
      other.buf = nullptr;
    }

    return *this;
  }
};

auto basic_and_classic::CastInCpp::describeCastInCpp() -> void {
  std::cout << "Q：阐述一下在C++中有哪些类型转换？" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif

  std::stringstream ss;
  std::cout << ss.str() << std::endl;
}

namespace basic_and_classic {
String::String() : data_(nullptr), size_(0) {
  std::cout << "Default constructor was called." << std::endl;
}

String::~String() {
  std::cout << "Destructor was called." << std::endl;
  delete[] data_;
}

String::String(const char* str) {
  std::cout << "Const char * constructor was called." << std::endl;

  if (!str) {
    data_ = new char[1];
    data_[0] = '\0';
    size_ = 0;
  } else {
    size_ = strlen(str);
    data_ = new char[size_ + 1];
    memcpy(data_, str, size_);
    data_[size_] = '\0';

    // also can use strcpy.
    // strcpy() copies the null-terminated byte string pointed to by src,
    // including the null terminator
    // strcpy(data, str);
  }
}

String::String(const String& other) noexcept{
  std::cout << "Copy constructor was called." << std::endl;

  size_ = other.size_;
  data_ = new char[size_ + 1];
  strcpy(data_, other.data_);
}

String& String::operator=(const String& other) {
  std::cout << "Copy assign operator was called." << std::endl;

  if (this == &other) {
    return *this;
  }

  delete[] data_;
  size_ = other.size_;
  data_ = new char[size_ + sizeof(char)];
  strcpy(data_, other.data_);

  return *this;
}

char& String::operator[](int i) {
  return data_[i];
}

const char& String::operator[](int i) const {
  return data_[i];
}

String String::operator+(const String& str) const {
  if (str.empty()) {
    return *this;
  }

  auto N = strlen(this->data_) + strlen(str.data_);
  char* buf = new char[N + 1];
  strcpy(buf, this->data_);
  strcat(buf, str.data_);

  return String(buf);
}

String String::operator+(const char* str) const{
  if (!str) {
    return *this;
  }

  auto N = strlen(this->data_) + strlen(str);
  char* buf = new char[N + 1];
  strcpy(buf, this->data_);
  strcat(buf, str);

  return String(buf);
}

String::String(String&& other) noexcept {
  std::cout << "Move constructor was called." << std::endl;

  this->size_ = other.size_;
  this->data_ = other.data_;

  other.size_ = 0;
  other.data_ = nullptr;
}

String::String(const std::string& str) {
  auto temp = str.c_str();
  this->size_ = strlen(temp);
  this->data_ = new char[this->size_ + 1];
  strcpy(this->data_, temp);
}

String& String::operator=(String&& other) noexcept {
  std::cout << "Move assign operator was called." << std::endl;

  if (this == &other) {
    return *this;
  }

  delete[] this->data_;
  this->size_ = other.size_;
  this->data_ = other.data_;

  other.size_ = 0;
  other.data_ = nullptr;
  return *this;
}

bool basic_and_classic::operator<(const String& st1, const String& st2) {
  return (std::strcmp(st1.data_, st2.data_) < 0);
}

bool basic_and_classic::operator>(const String& st1, const String& st2) {
  return st2 < st1;
}

bool basic_and_classic::operator==(const String& st1, const String& st2) {
  return (std::strcmp(st1.data_, st2.data_) == 0);
}

bool operator==(const String& st, const char* st2) {
  return (strcmp(st.data_, st2) == 0);
}

std::ostream& operator<<(std::ostream& os, const String& st) {
  if (st.data_) {
    os << st.data_;
  }
  return os;
}

std::istream& operator>>(std::istream& is, String& st) {
  std::string temp;
  std::cin >> temp;
  st = String(temp);
  return is;
}

bool String::empty() const {
  return size_ == 0;
}

int String::length() const {
  return size_;
}

int String::size() const {
  return length();
}

String& String::append(const String& other) {
  if (other.empty()) {
    return *this;
  }
  auto N = this->size_ + other.size_;
  char* buff = new char[N + 1];
  strcpy(buff, this->data_);
  strcat(buff, other.data_);
  delete[] this->data_;
  this->data_ = buff;
  this->size_ = N;

  return *this;
}

String& String::append(const char* str) {
  if (!str) {
    return *this;
  }
  auto N = this->size_ + strlen(str);
  char* buff = new char[N + 1];
  strcpy(buff, this->data_);
  strcat(buff, str);
  delete[] this->data_;
  this->data_ = buff;
  this->size_ = N;

  return *this;
}

void String::clear() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
}

char* String::data() const {
  return data_;
}

char* String::c_str() const {
  return data_;
}

}  // namespace basic_and_classic

auto basic_and_classic::CppCopyAssignDestoy::testMyString() -> void {
  if (0) {
    std::shared_ptr<String> str(new String);
    std::cout << *str << std::endl;
  }

  if (0) {
    String str("today is a good day.");
    std::cout << "s2 is : " << str << "size is: " << str.size() << std::endl;
  }

  if(0){
    String str1 = "hello,world";  // constructor --- String(const char*).
    // 等号左边的对象还未创建，所以调用拷贝构造。
    String str2 = str1;  // copy constructor --- String(const String &&).

    String str3 = std::move(str2);  // move constructor. --- String(String&& ).

    String str4;
    str4 = std::move(
        str3);  // move assign operator --- (String& operator=(String &&).
  }

  if(0){
    String str1("A"), str2("B");
    String str3 = str1 + str2;
    String str4 = str1 + "ambition";
    std::cout << "str1:" << str1 << std::endl;
    std::cout << "str2:" << str2 << std::endl;
    std::cout << "str3:" << str3 << std::endl;
    std::cout << "str4:" << str4 << std::endl;
  }

  if (0) {
    String str1("test");
    str1.append(" 001");
    String str2 = str1 + "chuanqi";
    std::cout << "str1:" << str1 << std::endl;
    std::cout << "str2:" << str2 << std::endl;
  }

  if (1) {
    std::cout << "Input a string:" << std::endl;
    String str;
    std::cin >> str;
    std::cout << "str: " << str << std::endl;
  }
}