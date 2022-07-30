#include <thread>
#include <iostream>
#include <string>

class greeter {
  public:
    // Thread entry point
    void hello()
    {
        std::cout << "Hello, Thread!\n";
    }
};

int main()
{
    // Create an object of the class
   greeter greet;

    // Use the member function pointer
    // Pass an object as the argument
    // to the member function call
    std::thread t{&greeter::hello, &greet};

    // Wait for the thread to complete
    t.join();
}

