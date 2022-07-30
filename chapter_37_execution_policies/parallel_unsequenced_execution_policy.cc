// Requires Visual C++ compiler or g++
#include <algorithm>
#include <vector>
#include <iostream>
#include <execution>

using namespace std::execution;

int main()
{
    std::vector<int> vec(2000);
    int count {0};
    std::for_each(par_unseq, begin(vec), end(vec), [&] (int& x) { x = ++count; });
}
