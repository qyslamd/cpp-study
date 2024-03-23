#ifdef _WINDOWS
#include<Windows.h>
#endif
#include "BasicAndClassic.h"
#include <sstream>
#include <iostream>

using namespace std;

void BasicAndClassic::execute() {
  std::vector<op::Question> ops{
      {"MemoryDistribute", "C/C++�ڴ�ֲ�", Memory::memDist},
      {"malloc() and operator new", "malloc��new������", Memory::mallocNewDiff},
      {"The 'static' keyword", "������static�ؼ��ֵ�����", StaticKeyword()},
      {"What's Rvalue reference in cpp11?", "��C++11��ʲô������ֵ���ã�", CppCopyAssignDestoy::lRef_rRef}};
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

void BasicAndClassic::StaticKeyword::operator()() {
  std::cout << "Q:static�ؼ�����C++������Щ�÷���" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif  // _WINDOWS

  std::stringstream ss;
  ss << "A:" << std::endl;
  ss << "1. ����ȫ�ֱ���" << std::endl;
  ss << "\tstatic ���ε�ȫ�ֱ�����ʾֻ�����ļ��ڿɼ�" << std::endl;
  ss << "2. ���ξֲ�����" << std::endl;
  ss << "\t��static���ξֲ�����ʱ���ñ���ֻ�ں����ڲ��ɼ������������ں�Ӧ��һ��"
        "������ֻ�ᱻ����һ�Ρ�"
     << std::endl;
  ss << "3. ������ĳ�Ա����" << std::endl;
  ss << "\t������ĳ�Ա������ʱ�򣬻��ܵ�public "
        "protected��private��Ӱ�졣�ñ��������౾������Ķ����޹ء�ʹ������::"
        "���������ʡ��������Ͷ�����Ҫ�ֿ���"
     << std::endl;
  ss << "4. ������ͨ����" << std::endl;
  ss << "\t���κ�����ʾ���ء��ɷ������޶�Ϊ�ļ��ڲ�" << std::endl;
  ss << "5. ������ĳ�Ա����" << std::endl;
  ss << "\t������������ĳ�Ա������" << std::endl;
  ss << "!!!�ر�ע��:�����һ��static "
        "ȫ�ֱ�����ͷ�ļ�����������ô#"
        "include��ͷ�ļ��������ط����ܷ��ʵ�������������Ǳ˴�֮�����"
     << std::endl;
  std::cout << ss.str() << std::endl;
}

void BasicAndClassic::CppCopyAssignDestoy::lRef_rRef() {
  std::cout << "Q:ʲô������ֵ���ã�" << std::endl;
#ifdef _WINDOWS
  system("pause");
#endif  // _WINDOWS
  std::stringstream ss;
  ss << "��ֵ���ò���'��'�������жϱ��ʽ�Ƿ����ȡ��ַ���޸��ж��Ƿ�����ֵ��" << std::endl;
  ss << "������˵û��ɵ�ƻ�ֱ��������������±ߵ�Demo���Կ�һ��:" << std::endl;
  ss << R"(
#include <iostream>
#include <string>
int main(){
    std::string s1 = "Test";
    //std::string && r1 = s1; // error,can't bind to lvalue.

    const std::string &r2 = s1 + s1;
    //r2 += "Test"; // error
    std::string && r3 = s1 + s1;
    r3 += "test";   // okay:can be modified through reference to non-const.
    std::cout << r3 << std::endl;
})"
     << std::endl;

  std::cout << ss.str() << std::endl;
}
