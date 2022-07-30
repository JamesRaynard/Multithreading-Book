#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

// The mutex objects to be locked
std::mutex mutex1;
std::mutex mutex2;

// C++17's std::scoped_lock tries to acquire both locks in a single operation
// One thread "wins" and locks both mutexes. The other thread waits.
// Eventually, the first thread unlocks both mutexes.
// This allows the other thread to lock the mutexes and proceed.

void func1() {
	std::cout << "Thread 1 locking mutexes..." << std::endl;
	std::scoped_lock lk1(mutex1, mutex2);
	std::cout << "Thread 1 has locked mutexes..." << std::endl;
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread 1 releasing mutexes..." << std::endl;
}

void func2() {
	std::cout << "Thread 2 locking mutexes..." << std::endl;
	std::scoped_lock lk1(mutex2, mutex1);
	std::cout << "Thread 2 has locked mutexes..." << std::endl;
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread 2 releasing mutexes..." << std::endl;
}

int main() {
	std::thread t1{ func1 };
	std::thread t2{ func2 };
	t1.join();
	t2.join();
}