#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

// The mutex objects to be locked
std::mutex mutex1;
std::mutex mutex2;

// Both threads try to lock the mutexes in the same order
// One thread "wins" and locks mutex 1, then mutex 2. The other thread waits.
// Eventually, the first thread unlocks the mutexes.
// This allows the other thread to lock mutex 1 and proceed.

// Lock mutex 1, then try to lock mutex 2
void func1() {
	// Use std::endl to make sure the output is displayed on all systems
	std::cout << "Thread 1 locking mutex 1..." << std::endl;
	std::unique_lock<std::mutex> lk1(mutex1);		// Acquire lock on mutex1
	std::cout << "Thread 1 has locked mutex 1" << std::endl;
	std::this_thread::sleep_for(50ms);	// Do some work
	std::cout << "Thread 1 locking mutex 2..." << std::endl;
	std::unique_lock<std::mutex> lk2(mutex2);		// Wait for lock on mutex2
	std::cout << "Thread 1 has locked mutex 2" << std::endl;
	std::this_thread::sleep_for(50ms);	// Do some work
	std::cout << "Thread 2 releases locks" << std::endl;
}

// Lock mutex 1, then try to lock mutex 2
void func2() {
	std::cout << "Thread 2 locking mutex 1..." << std::endl;
	std::unique_lock<std::mutex> lk2(mutex1);	// Wait for lock on mutex1
	std::cout << "Thread 2 has locked mutex 1" << std::endl;
	std::this_thread::sleep_for(50ms);	// Do some work
	std::cout << "Thread 2 locking mutex 2..." << std::endl;
	std::unique_lock<std::mutex> lk1(mutex2);	// Acquire lock on mutex2
	std::cout << "Thread 2 has locked mutex 2" << std::endl;
	std::this_thread::sleep_for(50ms);	// Do some work
	std::cout << "Thread 2 releases locks" << std::endl;
}

int main() {
	std::thread t1{ func1 };
	std::thread t2{ func2 };
	t1.join();
	t2.join();
}