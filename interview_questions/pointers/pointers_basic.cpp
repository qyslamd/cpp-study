#ifdef _WINDOWS
#include <Windows.h>
#endif

#include "pointers_basic.h"

#include "utils.h"

#include <sstream>
#include <iostream>

void pointer_basic ::execute() {
  op::Category factory("选择一个基础的问题或者命令，数字代表执行它",
                       {{"Pointer to an array.", "二维数组", _2DimArray}});
  factory.addGoBackOp();
  factory.execute();
}

void pointer_basic::_1DArray::test1() {

}

void pointer_basic::_2DimArray() {
  //_2DArrayPassParam obj;obj();

  _2DArrayPassParam::test();
  std::cout << std::endl;
}

void pointer_basic::_2DArrayPassParam::display1(int arr[][4],
                                                  const int irows) {
  for (int i = 0; i < irows; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << arr[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void pointer_basic::_2DArrayPassParam::display2(int (*arr)[4],
                                                const int irows) {
  for (int i = 0; i < irows; ++i) {
    for (int j = 0; j < 4; ++j) {
      std::cout << arr[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void pointer_basic::_2DArrayPassParam::display3(int* arr,
                                                const int irows,
                                                const int icols) {
  for (int i = 0; i < irows; ++i) {
    for (int j = 0; j < icols; ++j) {
      std::cout << *(arr + i * icols + j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void pointer_basic::_2DArrayPassParam::display4(int** arr, int rows, int cols) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      // *((int *)a +i*n +j )// n表示第二维数组长度,即列宽
      std::cout << *((int*)arr + cols * i + j) << std::endl;
    }
    std::cout << std::endl;
  }
}

void pointer_basic::_2DArrayPassParam::operator()() {
  int arr[4][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  auto temp = arr;  // int (*temp)[4]

  display1(arr, 4);

  display2(arr, 4);

  display3((int*)arr, 4, 4);

  display4((int**)arr, 4, 4);
}

void pointer_basic::_2DArrayPassParam::test001() {
  auto func1 = [](int(*arr)[]) { std::cout << arr << std::endl; };
  auto func2 = [](int(*arr)[3]) { std::cout << arr << std::endl; };

  int arr[2][3] = {1, 2, 3, 4, 5, 6};
  //func1(arr); // compile error.
  func2(arr);
}

void pointer_basic::_2DArrayPassParam::test() {
  /* 二维数组在内存中是连续存放的。很多教程是用一张表格表示的。
   * 例如：
   * int array[2][3] = {1,2,3,4,5,6};
   * array[0][0] = 1,
   * array[0][1] = 2,
   * array[0][2] = 3,
   * array[1][0] = 4,
   * array[1][1] = 5,
   * array[1][2] = 6,
   */

  /*
   * 对于不熟悉C/C++二级指针的人来说，可能会被以下的5种函数声明给迷惑到
   */

  //
  auto test1 = [](int arr[2][3]) {};
  auto test2 = [](int* arr) {};
  auto test3 = [](int(*arr)[3]) {};
  auto test4 = [](int** arr) {};
  auto test5 = [](int* arr[3]) {};
  auto test6 = [](int argc, char* argv[3]) {};

  /*
   * 将鼠标放在变量名上，tooltip提示会告诉你具体的类型。
   * test2就不说了，就是一个普通的指针。
   * 试过之后发现： test1 和 test3
   * 是一样的都是：int(*arr)[3];
   * 传参的时候是二维数组的首地址：什么是二维数组的首地址呢？(二维数组的名称就是它的首地址)
   *     二维数组的第一个元素可以看成第一行，所以二维数组的首地址应该是第一行的一维数组的地址，也就是数组指针。
   *     数组指针怎么定义? 当然是 int (*arr)[3],
   * 怎么阅读？先看括号，括号判断是指针，再看右边，右边是数组，所以是指向数组的指针。所以叫做数组指针
   *
   * test4 和 test5 是一样的，都是 : int **arr;
   * 这里有一个小技巧，通过main函数的形参来识别指针数组。
   * int main(int argc, char *argv[])
   *
   * char *argv[]和char** argv是一样的。但是 char *argv[]叫做
   * 指针数组。本质上是一个数组，数组的元素是指针。
   */

  std::stringstream ss;

  ss << "指针数组和数组指针的定义：" << std::endl;
  ss << "\t"
     << "1.指针数组: int *array[]" << std::endl;
  ss << "\t"
     << "2.数组指针: int (*ptr)[5]" << std::endl;
  ss << std::endl;

  ss << "二维数组作为函数参数的传递方式：\n";
  ss << "1. void func(int array[][5]); // "
        "最直接方式,且第二维必须显式指定!!!\n\n";
  ss << "2. void func(int (*arr)[5]);  // "
        "传递数组指针，即二维数组首地址，且第二维必须显式指定!!!\n\n";
  ss << "3. void func(int **arr, int row, int "
        "column);  // 使用指向指针的指针: 假设二维数组是 int "
        "arr[2][3]，那么调用的时候得: func((int**)arr, 2, 3); 寻址：*((int "
        "*)arr +i*n +j )//n表示第二维数组长度,即列宽\n\n";
  ss << "4. void func(int *arr, int row, int col);  // "
        "使用一维指针。使用起来和3差不多，但是只能是数组，实际传入参数不能为int"
        " **在堆上new或者malloc出来的\n\n";
  ss << std::endl;

#ifdef _WINDOWS
  system("cls");
#endif
  std::cout << ss.str() << "\n\n";
}