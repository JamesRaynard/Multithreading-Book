#include <atomic>
#include <thread>
#include <iostream>
#include <vector>

using namespace std::literals;

// Use atomic_flag as a simple lock
std::atomic_flag lock_cout = ATOMIC_FLAG_INIT;               // Initialize flag to false

void task(int n)
{
    while (lock_cout.test_and_set()) {}                      // "Lock" the flag
    std::this_thread::sleep_for(50ms);                       // Pretend to do some work
    std::cout << "I'm a task with argument " << n << "\n";
    lock_cout.clear();                                       // "Unlock" the flag
}

int main()
{
    std::vector<std::thread> threads;
    for (int i = 1; i <= 10; ++i)
        threads.push_back(std::thread{task, i});
    for (auto& th : threads)
    th.join();
}
