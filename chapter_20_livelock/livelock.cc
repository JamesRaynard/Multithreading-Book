#include <thread>
#include <mutex>
#include <iostream>

using namespace std::literals;

std::timed_mutex mutex1, mutex2;

void func1()
{
    std::this_thread::sleep_for(10ms);
    bool locked{false};
    while (!locked) {
        // Lock mutex1
        std::unique_lock<std::timed_mutex> lk(mutex1);
        std::this_thread::sleep_for(1s);        
        std::cout << "After you, Claude!\n";
        // Try to get a lock on mutex2
        locked = mutex2.try_lock_for(5ms);
    }
    if (locked)
        std::cout << "Thread1 has locked both mutexes";
}

void func2()
{
    bool locked{false};
    while (!locked) {
        // Lock mutex2
        std::unique_lock<std::timed_mutex> lk(mutex2);
        std::this_thread::sleep_for(1s);        
        std::cout << "No, after you, Cecil!\n";
        // Try to get a lock on mutex1
        locked = mutex1.try_lock_for(5ms);
    }
    if (locked)
        std::cout << "Thread2 has locked both mutexes\n";
}

int main()
{
    std::thread t1(func1);
    std::this_thread::sleep_for(10ms);
    std::thread t2(func2);
    t1.join();
    t2.join();
}
