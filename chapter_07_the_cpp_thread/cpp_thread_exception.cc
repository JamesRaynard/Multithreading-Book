#include <thread>
#include <iostream>

// Thread entry point
void hello()
{
    try {
        // Throw an exception
        throw std::exception();
    }
    catch(std::exception& e) {
        // Handle the exception
        std::cout << "Caught an exception\n";
    }
    std::cout << "Hello, Thread!\n";
}

int main() 
{
    // Create the thread object
    std::thread t{hello};
    t.join();

    // Check that the program is still running
    std::cout << "Finished\n";
}
