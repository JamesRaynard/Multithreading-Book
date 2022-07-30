#include <iostream>
#include <future>

// The task function
void hello()
{
    std::cout << "Hello, Async!\n";
}

int main()
{
    // Call std::async()
    // Pass the task function as argument
    std::async(hello);
}
