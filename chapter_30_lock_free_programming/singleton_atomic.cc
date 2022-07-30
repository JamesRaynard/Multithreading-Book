#include "singleton_atomic.h"
#include <thread>
#include <vector>

// Define the static member variable
std::atomic<Singleton *> Singleton::single{nullptr};

// Thread entry point function
void task()
{
    // Get the Singleton object
    Singleton* s = Singleton::get_singleton();

    // Display its address
    std::cout << s << "\n";
}

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
        threads.push_back(std::thread{task});
    for (auto& t : threads)
        t.join();
}
