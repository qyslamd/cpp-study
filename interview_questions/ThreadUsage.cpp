#include "ThreadUsage.h"
#include "utils.h"

#include <thread>
#include <chrono>

void ThreadUsage::execute() {
  std::vector<op::Question> ops{
      {"", "std::thread的基础用法", BasicThread::demo}};
  op::Category factory("Choose a question:", ops);
  factory.addGoBackOp();
  factory.execute();
}

auto ThreadUsage::BasicThread::demo() -> void {
  std::cout << __FUNCTION__ << "thread id:" << std::this_thread::get_id
            << std::endl;
  std::thread thread1([] {
      using namespace std::chrono_literals;
    std::cout << "thread id:" << std::this_thread::get_id << std::endl;
    std::this_thread::sleep_for(3s);
  });
  thread1.join();
}