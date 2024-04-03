#include "data_structure_algorithm.h"
#include "utils.h"

#include <memory>

#include "queue/array_make_queue.h"

void data_structure_algorithm::execute() {
  std::vector<op::Question> ops{{"Make queue use static array",
                                 "ʹ�þ�̬����ʵ�ֶ���",
                                 array_queue_demo::testStaticArrayQueue}};
  op::Category cate("ѡ������Ҫ�˽�����ݽṹ��Ȼ��ʼ", ops);
  cate.addGoBackOp();
  cate.execute();
}