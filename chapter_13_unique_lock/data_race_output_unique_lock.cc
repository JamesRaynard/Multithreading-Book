#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std::literals;

// Mutex to protect the critical region
std::mutex print_mutex;

auto print = [](const std::string& str)
{
    for (int i = 0; i < 5; ++i) {
    // Create the lock_guard object
    // This will lock the mutex
    std::unique_lock<std::mutex> lk(print_mutex);

    // The critical region, which modifies std::cout
    std::cout << str[0] << str[1] << str[2] << "\n";

    // Unlock the mutex
    lk.unlock();

    std::this_thread::sleep_for(50ms);
    } // Destroy the unique_lock object
};

int main()
{
    std::thread t1{print, "abc"};
    std::thread t2{print, "def"};
    std::thread t3{print, "xyz"};

    t1.join();
    t2.join();
    t3.join();
}
