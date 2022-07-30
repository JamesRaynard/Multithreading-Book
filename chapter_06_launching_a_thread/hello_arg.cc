#include <thread>
#include <iostream>
#include <string>

// Thread entry point now takes an std::string argument
void hello(std::string str)
{
    std::cout << str << "\n";
}

int main()
{
    // Create an std::thread object and initialize it
    // with the entry point function
    // Pass the argument to hello()
    std::thread t{hello, "Hello, Thread"};

    // Wait for the thread to complete
    t.join();
}

