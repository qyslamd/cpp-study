#pragma once

#include <iostream>
#include <memory>

namespace pointer_basic {
void execute();


/// <summary>
/// ��ϰ��ϰC/C++һάָ�����һά����
/// </summary>
struct _1DArray {
  static void test1();
};

struct _2DArrayPassParam {
	// ���ݶ�ά���飬�ڶ�ά������ʽָ��
  void display1(int arr[][4], const int irows);

  // һάָ�룬��������ָ�룬�ڶ�ά�������
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