#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <atomic>

#include "car_data.h"
#include "semaphore.h"

using std::mutex, std::thread, std::array, std::lock_guard;
using std::cout, std::cerr, std::string, std::vector;
using std::condition_variable, std::unique_lock, std::flush;

array<mutex, 4> resources, queue_in_dir;
vector<thread> ths;
thread dead_lock_detecting_th;
std::atomic_int	current_thread_total;
Semaphore sema(3);

void log(bool is_deadlock, bool is_arrive, const CarData *car_data_ptr) {
	static mutex mtx;
	
	if (is_deadlock) {
		lock_guard<mutex> lck(mutex);
		cout << "DEADLOCK: car jam detected\n" << flush;
		return;
	}

	string dir_name;
	switch (car_data_ptr->dir) {
		case Direction::kSouth:
			dir_name = "South";
			break;
		case Direction::kEast:
			dir_name = "East";
			break;
		case Direction::kNorth:
			dir_name = "North";
			break;
		case Direction::kWest:
			dir_name = "West";
			break;
	}
	string message = "car " + std::to_string(car_data_ptr->id) + " from " + dir_name + " ";
	if (is_arrive) message += "arrives at";
	else message += "leaving";
	message += " crossing\n";

	lock_guard<mutex> lck(mtx);
	cout << message << flush;
}

void DeadLockDetecting() {
	static bool tag = false;
	while (current_thread_total > 0) {
		if (sema.count() < 0 && !tag) {
			tag = true;
			log(true, false, nullptr);	
		} else if (sema.count() >= 0) {
			tag = false;
		}
	}
}

void CarPassing(CarData car_data) {
	int dir_id = static_cast<int>(car_data.dir);
	lock_guard<mutex> lck(queue_in_dir[dir_id]);
	sema.Wait();

	log(false, true, &car_data);

	resources[dir_id].lock();
	resources[(dir_id + 1) % 4].lock();
	resources[dir_id].unlock();
	resources[(dir_id + 1) % 4].unlock();

	log(false, false, &car_data);

	sema.Signal();
	current_thread_total--;
}

void Init(int argc, char **argv) {
	if (argc <= 1) {
		cerr << "Not sufficient command line arguments.\n";
		exit(1);
	}

	dead_lock_detecting_th = thread(DeadLockDetecting);

	current_thread_total = strlen(argv[1]);
	for (int i = 0, l = strlen(argv[1]); i < l; i++) {
		Direction dir;
		switch (argv[1][i]) {
			case 's':
				dir = Direction::kSouth;
				break;
			case 'e':
				dir = Direction::kEast;
				break;
			case 'n':
				dir = Direction::kNorth;
				break;
			case 'w':
				dir = Direction::kWest;
				break;
		}
		ths.emplace_back(CarPassing, CarData(dir, i + 1));
	}
}

void Go() {
	for (thread &th: ths) th.join();
	dead_lock_detecting_th.join();
}

int main(int argc, char **argv) {
	Init(argc, argv);
	Go();
	return 0;
}
