#include "BasicAndClassic.h"
#include <sstream>
#include <iostream>
#include <cstdio>

using namespace std;
namespace BasicAndClassic {

void BasicAndClassic::doQuestion(int argc, char* argv[]) {
  while (true) {
    Category cate;
    cout << "Choose your difficulty:" << endl
         << "\t" << CateToString(Category::Return, ": ") << endl
         << "\t" << CateToString(Category::MemDistribution, ": ") << endl;
    cin >> cate;
    cout << "You choosed:" << cate << endl;
    if (cate == Category::Return) {
      cout << "Function will return" << endl;
      return;
    }
    execute(cate);
  }
}

void BasicAndClassic::execute(Category cate) {
  switch (cate) {
    case BasicAndClassic::Category::MemDistribution:
      Memory::desc();
      break;
    default:
      break;
  }
}

void Memory::desc() {
  std::cout << "Q:��C/C++�У��ڴ��������Щ���ͣ�" << std::endl;
  getchar();
  std::stringstream ss;
  ss << "A:" << std::endl;
  ss << "1��[��]" << std::endl;
  ss << "\t ָ�롣ʹ��malloc����new���䣬�ɳ���Ա�����ͷ����ڴ�" << std::endl;
  ss << "2��[ջ]" << std::endl;
  ss << "\t "
        "�ֲ��������ߺ����������ɱ��������������ͷţ�ջ�Ŀռ����ޣ������ջ"
        "������̫���ڴ棬�п��ܵ���ջ���"
     << std::endl;
  ss << "3��[ȫ�֡���̬]" << std::endl;
  ss << "\t ȫ�ֱ����;�̬(static)�������ɱ��������������ͷš�" << std::endl;
  ss << "4��[�����洢��]" << std::endl;
  ss << "\t �洢����������ֵ�������ɱ��������������ͷš�" << std::endl;
  ss << "5��[�����������]" << std::endl;
  ss << "\t ��ų���Ķ����ƴ��룬�ɱ�����������ͷš�" << std::endl;

  std::cout << ss.str() << std::endl;
}
}  // namespace BasicAndClassic