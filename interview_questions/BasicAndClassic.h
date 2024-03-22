#pragma once
/*
* C/C++ 基础面试题，对于应届生来说最常见的问题
*/

#include <string>
#include <iostream>

#include "utils.h"

namespace BasicAndClassic {

struct Memory {
  void operator()();

  void memDist();

  void mallocNewDiff();
};

class StaticKeyword {
 public:
  static void askYou();
};

}  // namespace BasicAndClassic
