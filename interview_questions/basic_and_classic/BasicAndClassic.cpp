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
      {"MemoryDistribute", "C/C++�ڴ�ֲ�", Memory::memDist},
      {"malloc() and operator new", "malloc��new������", Memory::mallocNewDiff},
      {"The 'static' keyword", "������static�ؼ��ֵ�����", StaticKeyword()},
      {"What's Rvalue reference in cpp11?", "��C++11��ʲô������ֵ���ã�",
       CppCopyAssignDestoy::lRef_rRef},
      {"What's rules of three/five?", "C++�е�3/5�����Լ�0����",
       CppCopyAssignDestoy::_3_5_rules},
      {"Describe the explicit type conversion keyword in C++",
       "����C++�е���ʽ����ת���ؼ���", CastInCpp::describeCastInCpp},
      {"Write a string class", "�Լ�дһ��String��",
       CppCopyAssignDestoy::testMyString}};
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

void basic_and_classic::Memory::smartPointers() {
  std::cout << "����ͼ򵥼�¼��C++11���ṩ������ָ����÷���" << std::endl;

  std::stringstream ss;

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
    // �Ⱥ���ߵĶ���δ���������Ե��ÿ������졣
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