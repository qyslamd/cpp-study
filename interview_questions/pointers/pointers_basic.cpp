#include "pointers_basic.h"

#include "utils.h"

void pointer_basic ::execute() {
  std::vector<op::Question> ops{
      {"Pointer to an array.", "��ά����", _2DimArray}};
  op::Category factory("ѡ��һ���������������������ִ���ִ����", ops);
  factory.addGoBackOp();
  factory.execute();
}

void pointer_basic::_2DimArray() {
    // ��ά�������ִ��η�ʽ
}