#include <iostream>
#include <thread>
#include <chrono>

void hello(int num)
{
    auto delay = std::chrono::seconds(num);
    std::this_thread::sleep_for(delay);
    std::cout << "Hello from thread " << num << "\n";
}

int main()
{
    std::thread t1{hello, 1};
    std::thread t2{hello, 2};
    std::thread t3{hello, 3};

    t1.join();
    t2.join();
    t3.join();
}
