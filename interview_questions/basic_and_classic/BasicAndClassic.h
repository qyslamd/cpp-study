#pragma once
/*
* C/C++ ����
*/

#include <string>
#include <iostream>

namespace basic_and_classic {
void execute();

/// <summary>
/// �ڴ���ص�
/// </summary>
struct Memory {
  static void memDist();
  static void mallocNewDiff();
  static void smartPointers();
};

/// <summary>
/// Static �ؼ���
/// </summary>
struct StaticKeyword {
  void operator()();
};

/// <summary>
/// ��Ĵ����Ϳ���
/// </summary>
struct CppCopyAssignDestoy {
  static void lRef_rRef();
  static void _3_5_rules();
  /// <summary>
  /// ���������ǳ��������Ԫ��������������أ�constʹ�õ�
  /// </summary>
  /// <returns></returns>
  static auto testMyString() -> void;
};

/// <summary>
/// ����ת��
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
