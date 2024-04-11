#pragma once

#include <iostream>

namespace array_queue_demo {
/*
 * queue��һ��FIFO�����ݽṹ
 * ����ʹ�þ�̬���ݺͶ�̬������ʵ�֡�
 * ȱ�㣺1.��С�޶����������˾Ͳ�������Ӹ����Ԫ���ˣ����ǽ�һ�����������Ȼ�󿽱����½��������У�Ч�ʲ���
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
    // ��β����Ԫ��
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
  T data_array[N];  // ���÷�����ģ�����ָ����̬����Ĵ�С
  int front_;
  int rear_;
  int count_;
};

void testStaticArrayQueue();
}  // namespace array_queue_demo