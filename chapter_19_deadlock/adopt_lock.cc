#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

// The mutex objects to be locked
std::mutex mutex1;
std::mutex mutex2;

// C++11's std::lock tries to acquire both locks in a single operation.
// We then call std::unique_lock's constructor with the std::adopt_lock option,
// so it accepts a mutex which is already locked.

// One thread "wins" and locks both mutexes. The other thread waits.
// Eventually, the first thread unlocks both mutexes.
// This allows the other thread to lock the mutexes and proceed.

void func1() {
	std::cout << "Thread 1 locking mutexes..." << std::endl;
	std::lock(mutex1, mutex2);				               // Lock both mutexes
	std::cout << "Thread 1 has locked the mutexes..." << std::endl;
	std::unique_lock<std::mutex> lk1(mutex1, std::adopt_lock);   // Associate each mutex
	std::unique_lock<std::mutex> lk2(mutex2, std::adopt_lock);   // with a unique_lock
	std::cout << "Thread 1 releasing mutexes..." << std::endl;
}

void func2() {
	std::cout << "Thread 2 locking mutexes..." << std::endl;
	std::lock(mutex2, mutex1);				               // Lock both mutexes
	std::cout << "Thread 2 has locked the mutexes..." << std::endl;
	std::unique_lock<std::mutex> lk1(mutex1, std::adopt_lock);   // Associate each mutex
	std::unique_lock<std::mutex> lk2(mutex2, std::adopt_lock);   // with a unique_lock
	std::cout << "Thread 2 releasing mutexes..." << std::endl;
}

int main() {
	std::thread t1{ func1 };
	std::thread t2{ func2 };
	t1.join();
	t2.join();
}