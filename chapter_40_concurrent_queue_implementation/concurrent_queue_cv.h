#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

// Define a namespace for the concurrent queue
namespace cq {

// Exception to throw when popping an empty queue
class concurrent_queue_exception : public std::runtime_error {
    public:
    concurrent_queue_exception() : std::runtime_error("Queue is empty") {}
    concurrent_queue_exception(const char *s) : std::runtime_error(s) {}
};

// The concurrent queue class
template <class T>
class concurrent_queue {
    // The mutex to protect the queue
    std::mutex m;
    // The wrapped queue object
    std::queue<T> q;
    // The condition variable to signal new data
    std::condition_variable cv;
public:
    // Use defaults for the "Rule of Five"
    concurrent_queue() = default;

    // Thread-safe call to std::queue::push()
    void push(T value) {
        std::lock_guard<std::mutex> lg(m);
        q.push(value);
        cv.notify_one();
    }

    void pop(T& value) {
        // Lock the mutex
        std::unique_lock<std::mutex> lg(m);

        // Do not pop() an empty queue!
        cv.wait(lg, [this]() { return !q.empty(); });

        // Save the front element's value
        value = q.front();

        // Remove the front element
        q.pop();
    }
};
} // End of namespace cq

#endif //CONCURRENT_QUEUE_H
