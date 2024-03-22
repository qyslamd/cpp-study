#ifdef _WINDOWS
#include<Windows.h>
#endif
#include "BasicAndClassic.h"
#include <sstream>
#include <iostream>

using namespace std;

void BasicAndClassic::Memory::operator()() {
  std::vector<op::Question> ops{
      {"MemoryDistribute", "C/C++�ڴ�ֲ�", [this] { memDist(); }},
      {"malloc() and operator new", "malloc��new������",
       [this] { mallocNewDiff(); }}};
  op::Category factory("Choose a question:", ops);
  factory.addGoBackOp();
  factory.execute();
}

void BasicAndClassic::Memory::memDist() {
  std::cout << "Q:��C/C++�У��ڴ��������Щ���ͣ�" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif  // _WINDOWS

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

void BasicAndClassic::Memory::mallocNewDiff() {
  std::cout << "Q:malloc �� new ��ʲô����" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif  // _WINDOWS

  std::stringstream ss;
  ss << "A:" << std::endl;
  ss << "malloc ��C���Կ⺯����new��C++�еĹؼ��֣�Ҳ��һ�����Ա����صĲ�����"
     << std::endl;
  std::cout << ss.str() << std::endl;
}
