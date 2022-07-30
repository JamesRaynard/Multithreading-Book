#include <thread>
#include <iostream>
#include <string>

int main()
{

    // Use the member function pointer
    // Pass an object as the argument
    // to the member function call
    std::thread t{ []()
    {
        std::cout << "Hello, Thread!\n";
    }};

    t.join();

    // Lambda expression with capture by reference
    std::string str{"abc"};
    std::thread t2{ [&]()
    {
        str = "xyz";
    }};

    t2.join();

    std::cout << "str is now " << str << "\n";
}

