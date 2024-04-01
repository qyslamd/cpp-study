#pragma once

#include <iostream>
#include <memory>

namespace pointer_basic {
void execute();

struct _2DArrayPassParam {
	// 传递二维数组，第二维必须显式指定
  void passParam1(int arr[][4], const int irows);

  // 一维指针，传递数组指针，第二维必须标明
  void passParam2(int (*arr)[4], const int irows);

  // 
  void display3(int* arr, const int irows, const int icols);

  void display3(int** arr, int rows, int cols);
};

void _2DimArray();
}  // namespace pointer_basic