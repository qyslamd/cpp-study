// zero_started.cpp: 定义应用程序的入口点。
//

#include "zero_started.h"
#include <thread>
#include <string>

#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <fstream>
#include <algorithm>
#include <memory>
#include <atomic>
#include <future>
#include <condition_variable>
#include <mutex>
#include <functional>

#include <ctime>
#include <iomanip>

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
	task_running_ = true;
	for (int i = 0; i < task_count_; i++) {
		thread_vec_.push_back(std::make_shared<std::thread>(&Garren::threadWorker, this, i));
	}
}

Garren::~Garren()
{
	stop();
}

void Garren::stop()
{
	if (task_running_) {
		for (auto it = thread_vec_.begin(); it != thread_vec_.end(); ++it) {
			auto v = *it;
			if (v->joinable()) {
				v->join();
			}
		}
	}
}

void Garren::threadWorker(const int key)
{
	std::this_thread::sleep_for(std::chrono::seconds(2));

	using std::chrono::system_clock;
	std::time_t tt = system_clock::to_time_t(system_clock::now());

	struct std::tm* ptm = std::localtime(&tt);
	std::cout << "Current time: " << std::put_time(ptm, "%X") << '\n';

	std::cout << "Waiting for the next minute to begin...\n";
	++ptm->tm_min; ptm->tm_sec = 0;
	std::this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));

	std::cout << std::put_time(ptm, "%X") << " reached!\n";
}

class Zed
{
public:
	void say()
	{
		std::cout << "无形之刃，最为致命！" << " thread id:";
		std::cout << std::this_thread::get_id() << std::endl;
	}

	void niubi(int a)
	{
		std::cout << "均衡，是愚者的导师 原文链接：http://cnhbtc.com/yxlmyxtc/yxlmyxtc1726.html！" << a << " thread id:";
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

	auto func1 = std::bind(&Zed::niubi, zed, std::placeholders::_1);
	std::thread thread4(func1, 5);

	auto func2 = std::bind(&Zed::niubi, &zed, std::placeholders::_1);
	std::thread thread5(func2, 6);

	if (thread4.joinable()) {
		thread4.join();
	}

	if (thread5.joinable()) {
		thread5.join();
	}

	return 0;
}
