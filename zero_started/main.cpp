#include <iostream>
#include <sstream>

#include "zero_started.hpp"

int main(int argc, char* argv[]) {
  std::stringstream ss;
  ss << "In function:" << __FUNCTION__;
  ss << argc << "parameters are passed." << std::endl;
  ss << "they are:" << std::endl;
  for (int i = 0; i < argc; ++i) {
    ss << "\t" << argv[i] << std::endl;
  }
  std::cout << ss.str() << std::endl;

  zero_started::test_thread(argc, argv);

  return 0;
}
