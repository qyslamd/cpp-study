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
  /// ���������ǳ����
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

}  // namespace BasicAndClassic
