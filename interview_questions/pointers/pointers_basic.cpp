#include "pointers_basic.h"

#include "utils.h"

void pointer_basic ::execute() {
  std::vector<op::Question> ops{
      {"Pointer to an array.", "二维数组", _2DimArray}};
  op::Category factory("选择一个基础的问题或者命令，数字代表执行它", ops);
  factory.addGoBackOp();
  factory.execute();
}

void pointer_basic::_2DimArray() {
    // 二维数组三种传参方式
}