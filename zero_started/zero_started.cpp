// zero_started.cpp: 定义应用程序的入口点。
//

#include "zero_started.h"
#include <thread>
#include <string>

#include <vector>
#include <map>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <fstream>
#include <algorithm>
#include <memory>
#include <chrono>
#include <atomic>
#include <future>
#include <condition_variable>
#include <mutex>

static void hello()
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "hello,world" << " thread id:";
	std::cout << std::this_thread::get_id() << std::endl;
}

static void hello2(const std::string& str)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "hello, vs cmake project" << str << " thread id:";
	std::cout << std::this_thread::get_id() << std::endl;
}


Garren::Garren()
{

}

Garren::~Garren()
{
	if (task_running_) {
		for (auto it = thread_vec_.cbegin(); it != thread_vec_.cend(); ++it) {
		}

	}
}

void Garren::threadWorker(const int key)
{

}

class Zed
{
public:
	void say()
	{
		std::cout << "无形之刃，最为致命！" << " thread id:";
		std::cout << std::this_thread::get_id() << std::endl;
	}
};

int zero_started()
{
	std::cout << "Hello CMake." << " thread id:";
	std::cout << std::this_thread::get_id() << std::endl;

	std::thread thread(hello);
	std::thread thread2(hello2, "fuck you!");
	Zed zed;
	std::thread thread3(&Zed::say, &zed);

	if (thread.joinable()) {
		thread.join();
	}

	if (thread2.joinable()) {
		thread2.join();
	}

	if (thread3.joinable()) {
		thread3.join();
	}
	return 0;
}
