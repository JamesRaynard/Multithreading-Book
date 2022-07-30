#include <iostream>
#include <future>
#include <chrono>

using namespace std::literals;

// The task function
int func()
{
    std::cout << "Running in thread with ID "
              << std::this_thread::get_id() << "\n";
    std::this_thread::sleep_for(2s);
    return 42;
}

int main()
{
    std::cout << "Main thread with ID "
              << std::this_thread::get_id() << "\n";
    std::cout << "Starting task\n";

    // The task will be run in a separate thread
    auto result = std::async(std::launch::async, func);

    // The task will be run on this thread
    //auto result = std::async(std::launch::deferred, func);

    // The implememtation chooses how to run the task
    //auto result = std::async(func);

    // The implememtation chooses how to run the task
    //auto result = std::async(
    //              std::launch::async|std::launch::deferred,
    //              func);

    std::this_thread::sleep_for(1s);
    std::cout << "Calling get()\n";
    std::cout << result.get() << "\n";
}
