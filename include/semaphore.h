#pragma once

#include <mutex>
#include <condition_variable>

class Semaphore {
private:
	std::mutex mtx_;
	std::condition_variable cv_;
	int count_;

public:
	explicit Semaphore(int count);
	void Wait();
	void Signal();
};