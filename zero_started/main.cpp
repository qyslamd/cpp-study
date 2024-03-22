#include <iostream>
#include <sstream>

#include "zero_started.hpp"
#include "thread_usage.hpp"

int main(int argc, char *argv[]) {
  std::stringstream ss;
  ss << "command line parameters: " << std::endl;
  for (int i = 0; i < argc; ++i) {
    ss << "\targv[" << i << "]: " << argv[i] << std::endl;
  }
  std::cout << ss.str() << std::endl;

  cpp_study::zero_started::test_promise(argc, argv);

  cpp_study::thread_usage::std_thread::test_code();

  return 0;
}
