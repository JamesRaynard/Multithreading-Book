#include "thread_pool.h"
#include <iostream>
#include <mutex>
#include <chrono>

using namespace std::literals;

std::mutex m;

void task() {
    std::lock_guard<std::mutex> lg(m);
    std::cout << "Thread id: "
              << std::this_thread::get_id() << " started" << std::endl;
    std::this_thread::sleep_for(100ms);
    std::cout << "Thread id: "
              << std::this_thread::get_id() << " finished" << std::endl;
}

int main() {
    std::cout << "Creating a thread pool with "
              << std::thread::hardware_concurrency()
              << " threads" << std::endl;
    thread_pool pool;
    
    for (int i = 0; i < 20; ++i)
        pool.submit(task);
    
    std::this_thread::sleep_for(5s);
}
