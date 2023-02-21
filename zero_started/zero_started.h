// zero_started.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <thread>
#include <chrono>

int zero_started();


class Garren
{
public: 
	Garren();

	~Garren();

	void threadWorker(const int key);
private:
	void stop();
private:
	bool task_running_ = false;
	const int task_count_ = 1024;

	using ThreadVec = std::vector<std::shared_ptr<std::thread>>;

	ThreadVec thread_vec_;
};

