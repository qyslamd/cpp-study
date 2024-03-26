#pragma once

namespace ThreadUsage {
void execute();

struct BasicThread {
  static auto thread_demo() -> void;
  static auto mutex_lock_demo() -> void;
  static auto condition_variable_demo() -> void;
  static auto promise_demo() -> void;
  static auto packaged_task_demo() -> void;
  static auto async_demo() -> void;
  static auto call_once_demo() -> void;
  // �ϱߵ�ѧ���ˣ����Կ�ʼдһ���̳߳��ˡ�
  static auto thread_pool_demo() -> void;
};
}  // namespace ThreadUsage