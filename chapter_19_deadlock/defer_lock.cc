#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

// The mutex objects to be locked
std::mutex mutex1;
std::mutex mutex2;

// We call std::unique_lock's constructor with the std::defer_lock option,
// which allows the mutexes to be locked later.
// C++11's std::lock then tries to acquire both locks in a single operation.

// One thread "wins" and locks both mutexes. The other thread waits.
// Eventually, the first thread unlocks both mutexes.
// This allows the other thread to lock the mutexes and proceed.

void func1() {
	std::cout << "Thread 1 locking mutexes..." << std::endl;
	std::cout << "Thread 1 has locked the mutexes..." << std::endl;
	std::unique_lock<std::mutex> lk1(mutex1, std::defer_lock);       // Associate each mutex with a lock
	std::unique_lock<std::mutex> lk2(mutex2, std::defer_lock);       // ...but don’t lock it yet
	std::lock(lk1, lk2);				                             // Lock both mutexes
	std::cout << "Thread 1 releasing mutexes..." << std::endl;
}

void func2() {
	std::cout << "Thread 2 locking mutexes..." << std::endl;
	std::cout << "Thread 2 has locked the mutexes..." << std::endl;
	std::unique_lock<std::mutex> lk1(mutex1, std::defer_lock);       // Associate each mutex with a lock
	std::unique_lock<std::mutex> lk2(mutex2, std::defer_lock);       // ...but don’t lock it yet
	std::lock(lk2, lk1);				                             // Lock both mutexes
	std::cout << "Thread 2 releasing mutexes..." << std::endl;
}

int main() {
	std::thread t1{ func1 };
	std::thread t2{ func2 };
	t1.join();
	t2.join();
}