#pragma once

#include <iostream>
#include <memory>

namespace pointer_basic {
void execute();


/// <summary>
/// 复习复习C/C++一维指针或者一维数组
/// </summary>
struct _1DArray {
  static void test1();
};

struct _2DArrayPassParam {
	// 传递二维数组，第二维必须显式指定
  void display1(int arr[][4], const int irows);

  // 一维指针，传递数组指针，第二维必须标明
  void display2(int (*arr)[4], const int irows);

  // 
  void display3(int* arr, const int irows, const int icols);

  void display4(int** arr, int rows, int cols);

  void operator()();

  static void test001();

  static void test();
};

void _2DimArray();
}  // namespace pointer_basic