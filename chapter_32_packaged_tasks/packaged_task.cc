#include <iostream>
#include <future>

int main()
{
    // Create a packaged task. The task function
    // is a lambda expression which takes
    // two ints and returns an int
    std::packaged_task<int(int, int)> pkg{
        [](int a, int b) { return a + b; }};

    // The packaged task has an associated promise
    // Get the corresponding future for the promise
    // Use the task function's return type
    // for the type parameter
    std::future<int> fut = pkg.get_future();

    // Create an std::thread to run the task
    // Move the packaged_task into the constructor
    std::thread t{std::move(pkg), 6, 7};

    // Get the result of the task
    std::cout << "The result is: " << fut.get() << "\n";
    t.join();
}
