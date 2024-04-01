#ifdef _WINDOWS
#include<Windows.h>
#endif
#include "BasicAndClassic.h"
#include <sstream>
#include <iostream>
#include "utils.h"

using namespace std;

void basic_and_classic::execute() {
  std::vector<op::Question> ops{
      {"MemoryDistribute", "C/C++�ڴ�ֲ�", Memory::memDist},
      {"malloc() and operator new", "malloc��new������", Memory::mallocNewDiff},
      {"The 'static' keyword", "������static�ؼ��ֵ�����", StaticKeyword()},
      {"What's Rvalue reference in cpp11?", "��C++11��ʲô������ֵ���ã�",
       CppCopyAssignDestoy::lRef_rRef},
      {"What's rules of three/five?", "C++�е�3/5�����Լ�0����",
       CppCopyAssignDestoy::_3_5_rules},
      {"Describe the explicit type conversion keyword in C++",
       "����C++�е���ʽ����ת���ؼ���", CastInCpp::describeCastInCpp}};
  op::Category factory("ѡ��һ���������������������ִ���ִ����", ops);
  factory.addGoBackOp();
  factory.execute();
}

void basic_and_classic::Memory::memDist() {
  std::cout << "Q:��C/C++�У��ڴ��������Щ���ͣ�" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif  // _WINDOWS

  std::stringstream ss;
  ss << "A:" << std::endl;
  ss << "1��[��]" << std::endl;
  ss << "\t ָ�롣ʹ��malloc����new���䣬�ɳ���Ա�����ͷ����ڴ�" << std::endl;
  ss << "2��[ջ]" << std::endl;
  ss << "\t "
        "�ֲ��������ߺ����������ɱ��������������ͷţ�ջ�Ŀռ����ޣ������ջ"
        "������̫���ڴ棬�п��ܵ���ջ���"
     << std::endl;
  ss << "3��[ȫ�֡���̬]" << std::endl;
  ss << "\t ȫ�ֱ����;�̬(static)�������ɱ��������������ͷš�" << std::endl;
  ss << "4��[�����洢��]" << std::endl;
  ss << "\t �洢����������ֵ�������ɱ��������������ͷš�" << std::endl;
  ss << "5��[�����������]" << std::endl;
  ss << "\t ��ų���Ķ����ƴ��룬�ɱ�����������ͷš�" << std::endl;

  std::cout << ss.str() << std::endl;
}

void basic_and_classic::Memory::mallocNewDiff() {
  std::cout << "Q:malloc �� new ��ʲô����" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif  // _WINDOWS

  std::stringstream ss;
  ss << "A:" << std::endl;
  ss << "malloc ��C���Կ⺯����new��C++�еĹؼ��֣�Ҳ��һ�����Ա����صĲ�����"
     << std::endl;
  std::cout << ss.str() << std::endl;
}

void basic_and_classic::StaticKeyword::operator()() {
  std::cout << "Q:static�ؼ�����C++������Щ�÷���" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif  // _WINDOWS

  std::stringstream ss;
  ss << "A:" << std::endl;
  ss << "1. ����ȫ�ֱ���" << std::endl;
  ss << "\tstatic ���ε�ȫ�ֱ�����ʾֻ�����ļ��ڿɼ�" << std::endl;
  ss << "2. ���ξֲ�����" << std::endl;
  ss << "\t��static���ξֲ�����ʱ���ñ���ֻ�ں����ڲ��ɼ������������ں�Ӧ��һ��"
        "������ֻ�ᱻ����һ�Ρ�"
     << std::endl;
  ss << "3. ������ĳ�Ա����" << std::endl;
  ss << "\t������ĳ�Ա������ʱ�򣬻��ܵ�public "
        "protected��private��Ӱ�졣�ñ��������౾������Ķ����޹ء�ʹ������::"
        "���������ʡ��������Ͷ�����Ҫ�ֿ���"
     << std::endl;
  ss << "4. ������ͨ����" << std::endl;
  ss << "\t���κ�����ʾ���ء��ɷ������޶�Ϊ�ļ��ڲ�" << std::endl;
  ss << "5. ������ĳ�Ա����" << std::endl;
  ss << "\t������������ĳ�Ա������" << std::endl;
  ss << "!!!�ر�ע��:�����һ��static "
        "ȫ�ֱ�����ͷ�ļ�����������ô#"
        "include��ͷ�ļ��������ط����ܷ��ʵ�������������Ǳ˴�֮�����"
     << std::endl;
  std::cout << ss.str() << std::endl;
}

void basic_and_classic::CppCopyAssignDestoy::lRef_rRef() {
  std::cout << "Q:ʲô������ֵ���ã�" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif  // _WINDOWS
  std::stringstream ss;
  ss << "��ֵ���ò���'��'�������жϱ��ʽ�Ƿ����ȡ��ַ���޸��ж��Ƿ�����ֵ��" << std::endl;
  ss << "������˵û��ɵ�ƻ�ֱ��������������±ߵ�Demo���Կ�һ��:" << std::endl;
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
  std::cout << "Q����C++��ʲô����3/5����" << std::endl;
  #ifdef _WINDOWS
  system("pause");
  #endif

  std::stringstream ss;
  ss << "A:"
        "��һ�����У������������������Կ�����Ŀ����������������캯����������ֵ"
        "��������������������֮Ϊ���������°��C++"
        "11��׼�У���������ֵ���á������Զ���һ���ƶ����캯����һ���ƶ���ֵ����"
        "����0����ָ���ǵ��õ���Щ������ʱ������û�δ��ʽ�Ķ�����Щ��������ô���������Զ����ɡ�";
  ss << "�±���һ�������Ķ�����5�����������ʾ����" << std::endl;
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

namespace my_string_utility {
class MyString {
 public:
  MyString() : data(nullptr), size(0) {}
  ~MyString() {
    delete[] data;
    size = 0;
  }

  MyString(const char* str) {
    if (!str) {
      data = new char[1];
      data[0] = '\0';
      size = 0;
    }
    else {
      size = strlen(str);
      data = new char[size + 1];
      memcpy(data, str, size);
      data[size] = '\0';
    }
  }
  
  MyString(const MyString& other) {

  
  }
  MyString& operator=(const MyString& other) {}
  MyString(MyString&& other) {
  
  }
  MyString& operator=(MyString&& other) noexcept {}

 private:
  char* data;
  size_t size;
};
}  // namespace my_string_utility

auto basic_and_classic::CppCopyAssignDestoy::testMyString() -> void {}

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
  std::cout << "Q������һ����C++������Щ����ת����" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif

  std::stringstream ss;
  std::cout << ss.str() << std::endl;
}
