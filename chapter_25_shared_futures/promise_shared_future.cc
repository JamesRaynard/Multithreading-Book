#include <future>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals;

// Producer function with std::promise argument
void produce(std::promise<int>& px)
{
    int x{42};
    std::this_thread::sleep_for(1s);
    std::cout << "The promise sets the shared state to "
              << x << "\n";
    // Set the result
    px.set_value(x);
}

// Consumer function with std::future argument
void consume(std::shared_future<int>& fx)
{
    std::cout << "The future calls get()..." << "\n";
    // Get the result
    int x = fx.get();
    std::cout << "The future returns from get()\n";
    std::cout << "The answer is " << x << "\n";
}

int main()
{
    std::promise<int> p;

    // Move the promise's future into a shared future
    std::shared_future<int> sf1{p.get_future()};

    // Make a copy for the second consumer thread
    std::shared_future<int> sf2 = sf1;

    // Start two consumer threads
    // Each has its own copy of the shared future
    std::thread fut1{consume, std::ref(sf1)};
    std::thread fut2{consume, std::ref(sf2)};

    // Start the producer thread
    // Pass the promise to it
    std::thread prom{produce, std::ref(p)};

    fut1.join();
    fut2.join();
    prom.join();
}

