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
  /// 考察深拷贝和浅拷贝
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

}  // namespace BasicAndClassic
