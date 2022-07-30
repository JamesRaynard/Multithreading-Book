#include <thread>
#include <iostream>

class thread_guard {
    std::thread t;
public:
    // explicit constructor prevents conversions
    // std::thread is move-only, so the
    // constructor takes an rvalue reference
    explicit thread_guard(std::thread t) : t(std::move(t)) {}

    ~thread_guard()
    {
        // Join the thread if not already joined
        if (t.joinable()) t.join();
    }

    // Prevent copying by declaring
    // the copy operators as deleted

    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete; 
};

// Callable object - thread entry point
void hello()
{
    std::cout << "Hello, Thread!\n";
}

int main()
{
  try {
    //std::thread t{ hello };
    thread_guard tg{ std::thread(hello) };
    throw std::exception();
  }
  catch (std::exception& e) {
    std::cout << "Exception caught\n";
  }
}
