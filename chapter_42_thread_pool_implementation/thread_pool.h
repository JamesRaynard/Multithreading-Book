#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "concurrent_queue_cv.h"
#include <atomic>
#include <thread>
#include <functional>
#include <vector>

// Type alias to simplify the code
using Func = std::function<void()>;

class thread_pool {
    // The concurrent queue of task functions
    cq::concurrent_queue<Func> work_queue;

    // The container of threads
    std::vector<std::thread> threads;

    // The entry point function for the threads
    void worker();
public:
    thread_pool();
    ~thread_pool();

    // Member function to push a task on the queue
    void submit(Func f);
};

#endif //THREAD_POOL_H
