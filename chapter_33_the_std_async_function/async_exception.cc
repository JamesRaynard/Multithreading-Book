#include <iostream>
#include <future>

using namespace std::literals;

int func()
{
    int x{42};
    std::this_thread::sleep_for(2s);
    throw std::out_of_range("Oops");
    return x;
}

int main()
{
    auto f = std::async(func);

    try {
        auto result = f.get();
        std::cout << "Result: " << result << "\n";
    }
    catch (std::exception& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }
}
