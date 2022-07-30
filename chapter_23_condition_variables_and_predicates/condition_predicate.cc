#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <chrono>

using namespace std::literals;

// Global variables
std::mutex mut;
std::condition_variable cv;
std::string sdata{"Empty"};

// Flag for predicate
bool condition{false};

// Waiting thread
void reader()
{
    // Acquire lock
    std::unique_lock<std::mutex> guard(mut);
 
    // Unlock the mutex and
    // wait for condition variable to be notified
    cv.wait(guard, []() { return condition; });
    
    // Wake up and use the new value
    // The mutex is now locked again
    std::cout << "Data is " << sdata << "\n";
}

// Modyifing thread
void writer()
{
    std::cout << "Writing data...\n";
    {
        // Acquire lock
        std::lock_guard<std::mutex> lg(mut);

        // Pretend to be busy...
        std::this_thread::sleep_for(2s);

        // Modify the data
        sdata = "Populated";
        condition = true;
    }

    // Notify the condition variable
    // The mutex is now unlocked
    cv.notify_one();
}

int main()
{
    std::cout << "Data is " << sdata << "\n";
    std::thread read{reader};
    std::thread write{writer};
    write.join();
    read.join();
}
