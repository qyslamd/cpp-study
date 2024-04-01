#pragma once

#include <iostream>
#include <memory>

namespace pointer_basic {
void execute();

struct _2DArrayPassParam {
	// ���ݶ�ά���飬�ڶ�ά������ʽָ��
  void passParam1(int arr[][4], const int irows);

  // һάָ�룬��������ָ�룬�ڶ�ά�������
  void passParam2(int (*arr)[4], const int irows);

  // 
  void display3(int* arr, const int irows, const int icols);

  void display3(int** arr, int rows, int cols);
};

void _2DimArray();
}  // namespace pointer_basic