#include <thread>
#include <iostream>
#include <vector>

// Shared integer
volatile int counter {0};

// Thread entry point
void task()
{
    // Do we need a lock here?
    for (int i = 0; i < 100'000; ++i)
        ++counter;
}

int main()
{
    std::vector<std::thread> tasks;
    for (int i = 0; i < 10; ++i)
        tasks.push_back(std::thread{task});
    for (auto& t: tasks)
        t.join();
    std::cout << counter << "\n";
}
