#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>

// Requires Visual C++ compiler or g++
//#include <execution>
//using namespace std::execution;

int main()
{
    // The predicted results
    std::vector<double> expected{0.1, 0.2, 0.3, 0.4, 0.5};

    // The results of the experiment
    std::vector<double> actual{0.09, 0.22, 0.27, 0.41, 0.52};

    auto max_err = std::transform_reduce(
	                  //par_unseq,  // Requires Visual C++ compiler or g++
                      begin(expected), end(expected),
                     
                      begin(actual),
                      // Initial maximum error
                      0.0,
                      // The reduce operation finds the biggest difference
                      [](auto a, auto b) { return std::max(a, b); },
                      // The transform operation finds each difference
                      [](auto l, auto r) { return std::fabs(l - r); });
    std::cout << "The largest error is " << max_err << "\n";
}
