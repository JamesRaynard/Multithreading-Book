#include <thread>
#include <iostream>

// Thread entry point function
void hello()
{
    std::cout << "Hello, Thread!\n";
}

int main()
{
    // Create an std::thread object and initialize it
    // with a callable object
        // A function pointer to the entry point function
    std::thread t{hello};

    // Wait for the thread to complete
    t.join();
}

