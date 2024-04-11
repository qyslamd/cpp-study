#pragma once

#include <iostream>

namespace array_queue_demo {
/*
 * queue是一中FIFO的数据结构
 * 可以使用静态数据和动态数组来实现。
 * 缺点：1.大小限定，队列满了就不能再添加更多的元素了，除非建一个更大的数组然后拷贝到新建的数组中，效率不高
 */
template <typename T, int N>
class StaticArrayQueue {
 public:
  StaticArrayQueue() : front_(0), rear_(0), count_(0) {}
  StaticArrayQueue(const StaticArrayQueue& other) {}

  int count() const { return count_; }
  bool empty() const { return count_ == 0; }

  bool full() const { return count_ == N - 1; }

  bool enqueue(const T& t) {
    if (full()) {
      return false;
    }
    // 队尾放置元素
    data_array[rear_++] = t;
    count_ += 1;
    return true;
  }

  T dequeue() {
    if (empty()) {
      return T{};
    }
    auto const t = data_array[front_++];
    count_ -= 1;
    return t;
  }

  T& head() {
    if (empty()) {
      return T{};
    }
    return data_array[front_];
  }

  const T& head() const {
    if (empty()) {
      return T{};
    }
    return data_array[front_];
  }

  void dumpStr() const {
    std::cout << "queue is " << (empty() ? "" : "not ") << "empty!"
              << std::endl;
    std::cout << "count of queue:" << count() << std::endl;
    std::cout << "queue is " << (full() ? "" : "not ") << "full!"
              << std::endl;
  }

 private:
  T data_array[N];  // 利用非类型模板参数指定静态数组的大小
  int front_;
  int rear_;
  int count_;
};

void testStaticArrayQueue();
}  // namespace array_queue_demo