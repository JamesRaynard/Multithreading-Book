#include "concurrent_queue_cv.h"
#include <iostream>
#include <future>
#include <string>
#include <thread>
#include <chrono>

using namespace std::literals;

// Create a concurrent queue object
cq::concurrent_queue<std::string> conc_queue;
    
// Waiting thread
void reader() {
    std::string sdata;
    // Pretend to be busy...
    std::this_thread::sleep_for(2s);

    std::cout << "Reader calling pop...\n";

    // Pop the data off the queue
    conc_queue.pop(sdata);                                       
    std::cout << "Reader received data: " << sdata << "\n";
}

// Modyifing thread
void writer() {
    std::cout << "Writer calling push...\n";

    // Push the data onto the queue
    conc_queue.push("Populated");                                    
    std::cout << "Writer returned from push...\n";
}

int main() {
    auto w = std::async(std::launch::async, writer);
    auto r = std::async(std::launch::async, reader);
    r.wait();
    w.wait();
}
