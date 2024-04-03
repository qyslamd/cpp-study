#include "array_make_queue.h"

void array_queue_demo::testStaticArrayQueue() {
  StaticArrayQueue<int, 5> myQueue;
  myQueue.dumpStr();

  myQueue.enqueue(5);
}
