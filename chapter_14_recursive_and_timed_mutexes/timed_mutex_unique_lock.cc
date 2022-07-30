#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

std::timed_mutex the_mutex;

void task1()
{
    std::cout << "Task1 trying to get lock\n";
    std::unique_lock<std::timed_mutex> lk(the_mutex);
    std::cout << "Task1 has lock\n";
    std::this_thread::sleep_for(500ms);
    std::cout << "Task1 releasing lock\n";
}

void task2()
{
    std::this_thread::sleep_for(100ms);
    std::cout << "Task2 trying to get lock\n";

    // Find a timepoint 100ms in the future
    auto deadline = std::chrono::steady_clock::now() + 100ms;
    std::unique_lock<std::timed_mutex> lk(the_mutex, deadline);

    // Keep trying to lock until the deadline is reached
    while (!lk.owns_lock()) {
        std::cout << "Task2 could not get lock\n";

        // Advance the timepoint by 100ms
        deadline += 100ms;
        lk.try_lock_until(deadline);
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
