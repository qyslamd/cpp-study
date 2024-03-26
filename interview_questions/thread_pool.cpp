#include "thread_pool.hpp"

namespace thread_pool {
threadpool ::threadpool(unsigned short size) : thread_size(size) {
  addThread(size);
}

threadpool::~threadpool() {
  _run = false;
  _task_cv.notify_all();
  for (std::thread& thread : _pool) {
    if (thread.joinable())
      thread.join();
  }
}
}  // namespace thread_pool