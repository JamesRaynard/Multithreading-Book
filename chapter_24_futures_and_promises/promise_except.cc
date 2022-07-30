#include <future>
#include <iostream>
#include <thread>
#include <exception>
#include <chrono>

using namespace std::literals;

// Producer function with std::promise argument
void produce(std::promise<int>& px)
{               
    try {
        int x{42};
        std::this_thread::sleep_for(1s);
        throw std::out_of_range("Oops");
        std::cout << "The promise sets the shared state"
                  << " to " << x << "\n";
        // Set the result
        px.set_value(x);                           
    }
    catch(...) {
        px.set_exception(std::current_exception());
    }
}

// Consumer function with std::future argument
void consume(std::future<int>& fx)
{                
    std::cout << "The future calls get()...\n";
    try {
        // Get the result
        int x = fx.get();                           
        std::cout << "The future returns from get()\n";
        std::cout << "The answer is " << x << "\n";
    }
    catch(std::exception& e) {
        std::cout << "Exception caught: "
                  << e.what() << "\n";
    }
}

int main()
{
    // Create the promise object
    std::promise<int> p;

    // Obtain the associated future
    std::future<int> f = p.get_future();
    
    // Start the consumer thread
    // Pass the future to it
    std::thread fut{consume, std::ref(f)};

    // Start the producer thread
    // Pass the promise to it
    std::thread prom{produce, std::ref(p)};
    
    fut.join();
    prom.join();
}
