#include "thread_pool.h"

// Thread entry point function
void thread_pool::worker() {
    // Infinite loop
    while (true) {
        Func task;

        // Get the next task from the queue
        work_queue.pop(task);

        // Call the task function
        task();
    }
}

// Thread pool constructor
thread_pool::thread_pool() {
    // Find the number of hardware threads
    const unsigned thread_count = std::thread::hardware_concurrency();

    // Create that number of std::thread objects
    // Use worker() as the entry point
    // Populate the container
    for (unsigned i = 0; i < thread_count; ++i)
        threads.push_back(std::thread{&thread_pool::worker, this});
}

// Destructor
thread_pool::~thread_pool() {
    // Join all the threads in the container
    for (auto& t: threads) {
        t.join();
    }
}

// Function for clients to submit tasks
void thread_pool::submit(Func f) {
    work_queue.push(f);
}
