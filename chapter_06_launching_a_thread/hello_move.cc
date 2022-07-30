#include <thread>
#include <iostream>
#include <string>

// Thread entry point
void func(std::string s)
{
    std::cout << "All your string are belong to us: "
            << s << "\n";
}

int main()
{
    // This will be the argument to hello()
   std::string str{"abc"};

    // Pass the argument by move
    std::thread t{func, std::move(str)};

    // Wait for the thread to complete
    t.join();

    // Verify that the string has been modified
    std::cout << "str is now " << str << "\n";
}

