#pragma once

#include <mutex>
#include <condition_variable>
#include <atomic>

class Semaphore {
private:
	std::mutex mtx_;
	std::condition_variable cv_;
	std::atomic_int count_;

public:
	explicit Semaphore(int count);
	void Wait();
	void Signal();
	int count() const;
};