#include "singleton.h"
#include <thread>
#include <vector>

// Define the static member variable
Singleton *Singleton::single = 0;

// Thread entry point function
void task()
{
    // Get the Singleton object
    Singleton* s = Singleton::get_singleton();

    // Display its address
    std::cout << s << std::endl;
}

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
        threads.push_back(std::thread{task});
    for (auto& t : threads)
        t.join();
}
