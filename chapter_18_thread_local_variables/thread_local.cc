#include <random>
#include <thread>
#include <iostream>

using namespace std::literals;

// Each thread will have its own engine object.
// Each object should generate the same sequence
thread_local std::mt19937 mt;

void func() {
	std::uniform_real_distribution<double> dist(0, 1);  // Doubles in the range 0 to 1

	for (int i = 0; i < 10; ++i)                        // Generate 10 random numbers
		std::cout << dist(mt) << ", ";
}

int main() {
	std::cout << "Thread 1's random values:" << "\n";
	std::thread t1{ func };
	t1.join();
	std::this_thread::sleep_for(100ms);
	
	// Thread 2 should display the same sequence as thread 1
	std::cout << "\nThread 2's random values:" << "\n";
	std::thread t2{ func };
	t2.join();
	std::cout << "\n";
}