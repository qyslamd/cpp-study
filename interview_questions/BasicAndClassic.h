#pragma once
/*
* C/C++ 基础面试题，对于应届生来说最常见的问题
*/

#include <string>
#include <iostream>

#include "utils.h"

namespace BasicAndClassic {
struct Memory {
  static void memDist();
  static void mallocNewDiff();
};

struct StaticKeyword {
  void operator()();
};

struct CppCopyAssignDestoy {
  static void lRef_rRef();
  static void _3_5_rules();
};

void execute();

}  // namespace BasicAndClassic
