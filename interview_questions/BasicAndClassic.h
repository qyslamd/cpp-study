#pragma once
/*
* C/C++ ���������⣬����Ӧ������˵���������
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
