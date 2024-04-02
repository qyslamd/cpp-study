#pragma once
/*
* C/C++ 基础
*/

#include <string>
#include <iostream>

namespace basic_and_classic {
void execute();

/// <summary>
/// 内存相关的
/// </summary>
struct Memory {
  static void memDist();
  static void mallocNewDiff();
  static void smartPointers();
};

/// <summary>
/// Static 关键字
/// </summary>
struct StaticKeyword {
  void operator()();
};

/// <summary>
/// 类的创建和拷贝
/// </summary>
struct CppCopyAssignDestoy {
  static void lRef_rRef();
  static void _3_5_rules();
  /// <summary>
  /// 考察深拷贝和浅拷贝，友元函数，运算符重载，const使用等
  /// </summary>
  /// <returns></returns>
  static auto testMyString() -> void;
};

/// <summary>
/// 类型转换
/// </summary>
struct CastInCpp {
  static auto describeCastInCpp() -> void;
};

class String {
  // Constructors.
 public:
  String();
  ~String();
  String(const char* str);
  String(const std::string& str);
  String(const String& other) noexcept;
  String(String&& other) noexcept;

  // overload operators.
 public:
  String& operator=(const String& other);
  String& operator=(String&& other) noexcept;
  char& operator[](int i);
  const char& operator[](int i) const;
  String operator+(const String& st) const;
  String operator+(const char* s) const;
  // overloaded operator friends
 public:
  friend bool operator<(const String& st, const String& st2);
  friend bool operator>(const String& st1, const String& st2);
  friend bool operator==(const String& st, const String& st2);
  friend bool operator==(const String& st, const char* st2);
  friend std::ostream& operator<<(std::ostream& os, const String& st);
  friend std::istream& operator>>(std::istream& is, String& st);

 public:
  bool empty() const;
  int length() const;
  int size() const;
  String& append(const String& other);
  String& append(const char* s);
  void clear();
  char* data() const;
  char* c_str() const;

 private:
  static const int CINLIM = 80;
  char* data_;
  int size_;
};
}  // namespace basic_and_classic
