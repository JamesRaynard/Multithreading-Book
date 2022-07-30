// Requires Visual C++ compiler or g++
#include <algorithm>
#include <vector>
#include <exception>
#include <iostream>
#include <execution>

using namespace std::execution;

int main()
{
    std::vector<int> vec{3,1,4,1,5,9};
    try {
		// Call the std::sort() algorithm
		// with a predicate that throws an exception
        std::sort(seq, begin(vec), end(vec), [](int a, int b) {
            throw std::out_of_range("Oops"); return true;}
        );
    }
    catch (std::exception& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }
}
