#include "semaphore.h"

using std::unique_lock, std::mutex, std::lock_guard;

Semaphore::Semaphore(int count): count_(count) {}

void Semaphore::Wait() {
	unique_lock<mutex> lck(mtx_);
	count_--;
	if (count_ < 0)
		cv_.wait(lck);
}

void Semaphore::Signal() {
	lock_guard<mutex> lck(mtx_);
	count_++;
	if (count_ <= 0)
		cv_.notify_one();
}

int Semaphore::count() const {
	return count_;
}