#ifdef _WINDOWS
#include <Windows.h>
#endif

#include "pointers_basic.h"

#include "utils.h"

#include <sstream>
#include <iostream>

void pointer_basic ::execute() {
  op::Category factory("ѡ��һ���������������������ִ���ִ����",
                       {{"Pointer to an array.", "��ά����", _2DimArray}});
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
      // *((int *)a +i*n +j )// n��ʾ�ڶ�ά���鳤��,���п�
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
  /* ��ά�������ڴ�����������ŵġ��ܶ�̳�����һ�ű���ʾ�ġ�
   * ���磺
   * int array[2][3] = {1,2,3,4,5,6};
   * array[0][0] = 1,
   * array[0][1] = 2,
   * array[0][2] = 3,
   * array[1][0] = 4,
   * array[1][1] = 5,
   * array[1][2] = 6,
   */

  /*
   * ���ڲ���ϤC/C++����ָ�������˵�����ܻᱻ���µ�5�ֺ����������Ի�
   */

  //
  auto test1 = [](int arr[2][3]) {};
  auto test2 = [](int* arr) {};
  auto test3 = [](int(*arr)[3]) {};
  auto test4 = [](int** arr) {};
  auto test5 = [](int* arr[3]) {};
  auto test6 = [](int argc, char* argv[3]) {};

  /*
   * �������ڱ������ϣ�tooltip��ʾ��������������͡�
   * test2�Ͳ�˵�ˣ�����һ����ͨ��ָ�롣
   * �Թ�֮���֣� test1 �� test3
   * ��һ���Ķ��ǣ�int(*arr)[3];
   * ���ε�ʱ���Ƕ�ά������׵�ַ��ʲô�Ƕ�ά������׵�ַ�أ�(��ά��������ƾ��������׵�ַ)
   *     ��ά����ĵ�һ��Ԫ�ؿ��Կ��ɵ�һ�У����Զ�ά������׵�ַӦ���ǵ�һ�е�һά����ĵ�ַ��Ҳ��������ָ�롣
   *     ����ָ����ô����? ��Ȼ�� int (*arr)[3],
   * ��ô�Ķ����ȿ����ţ������ж���ָ�룬�ٿ��ұߣ��ұ������飬������ָ�������ָ�롣���Խ�������ָ��
   *
   * test4 �� test5 ��һ���ģ����� : int **arr;
   * ������һ��С���ɣ�ͨ��main�������β���ʶ��ָ�����顣
   * int main(int argc, char *argv[])
   *
   * char *argv[]��char** argv��һ���ġ����� char *argv[]����
   * ָ�����顣��������һ�����飬�����Ԫ����ָ�롣
   */

  std::stringstream ss;

  ss << "ָ�����������ָ��Ķ��壺" << std::endl;
  ss << "\t"
     << "1.ָ������: int *array[]" << std::endl;
  ss << "\t"
     << "2.����ָ��: int (*ptr)[5]" << std::endl;
  ss << std::endl;

  ss << "��ά������Ϊ���������Ĵ��ݷ�ʽ��\n";
  ss << "1. void func(int array[][5]); // "
        "��ֱ�ӷ�ʽ,�ҵڶ�ά������ʽָ��!!!\n\n";
  ss << "2. void func(int (*arr)[5]);  // "
        "��������ָ�룬����ά�����׵�ַ���ҵڶ�ά������ʽָ��!!!\n\n";
  ss << "3. void func(int **arr, int row, int "
        "column);  // ʹ��ָ��ָ���ָ��: �����ά������ int "
        "arr[2][3]����ô���õ�ʱ���: func((int**)arr, 2, 3); Ѱַ��*((int "
        "*)arr +i*n +j )//n��ʾ�ڶ�ά���鳤��,���п�\n\n";
  ss << "4. void func(int *arr, int row, int col);  // "
        "ʹ��һάָ�롣ʹ��������3��࣬����ֻ�������飬ʵ�ʴ����������Ϊint"
        " **�ڶ���new����malloc������\n\n";
  ss << std::endl;

#ifdef _WINDOWS
  system("cls");
#endif
  std::cout << ss.str() << "\n\n";
}