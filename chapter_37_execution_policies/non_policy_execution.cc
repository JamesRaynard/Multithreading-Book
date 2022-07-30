// Requires Visual C++ compiler or g++
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

using namespace std::execution;

int main()
{
    std::vector<int> vec(2'000);
    int count{0};
    std::for_each(par, begin(vec), end(vec),
                  [&](int& x) { x = ++count; });
}
