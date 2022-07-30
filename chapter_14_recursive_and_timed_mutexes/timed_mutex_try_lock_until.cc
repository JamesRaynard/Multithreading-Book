#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

std::timed_mutex the_mutex;

void task1()
{
    std::cout << "Task1 trying to get lock\n";
    the_mutex.lock();
    std::cout << "Task1 has lock\n";
    std::this_thread::sleep_for(500ms);
    std::cout << "Task1 releasing lock\n";
    the_mutex.unlock();
}

void task2()
{
    std::this_thread::sleep_for(100ms);
    std::cout << "Task2 trying to get lock\n";

    // Find a timepoint 100ms in the future
    auto deadline = std::chrono::steady_clock::now() + 100ms;

    // Keep trying to lock until the deadline is reached
    while (!the_mutex.try_lock_until(deadline)) {
        std::cout << "Task2 could not get lock\n";
        // Advance the timepoint by 100ms
        deadline += 100ms;
    }
    std::cout << "Task2 has lock\n";
    the_mutex.unlock();
}

int main()
{
    std::thread t1{task1}, t2{task2};
    t1.join();
    t2.join();
}
