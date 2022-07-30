#include <thread>
#include <iostream>
#include <string>

// Thread entry point now takes its argument by reference
void hello(std::string& s)
{
    s = "xyz";
}

int main()
{
    // This will be the argument to hello()
    std::string str{"abc"};

    // Pass the argument by reference
    std::thread t{hello, std::ref(str)};

    // Wait for the thread to complete
    t.join();

    // Verify that the string has been modified
    std::cout << "str is now " << str << "\n";
}

