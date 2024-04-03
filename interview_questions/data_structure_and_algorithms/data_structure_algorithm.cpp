#include "data_structure_algorithm.h"
#include "utils.h"

#include <memory>

#include "queue/array_make_queue.h"

void data_structure_algorithm::execute() {
  std::vector<op::Question> ops{{"Make queue use static array",
                                 "使用静态数组实现队列",
                                 array_queue_demo::testStaticArrayQueue}};
  op::Category cate("选择你想要了解的数据结构，然后开始", ops);
  cate.addGoBackOp();
  cate.execute();
}