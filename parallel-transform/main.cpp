/**
    This shows using parallel transform_reduce from C++17
    to perform a fold (reduce) operation on a range of values. e.g. sum up 100 values in parallel
*/
#include <vector>
#include <numeric>    // std::transform_reduce
#include <functional> // std::plus
#include <iostream>
#include <execution> // std::execution::par

int
main()
{
    std::vector<int> numbers(100);
    // Initialize the vector with values 1 to 100
    std::iota(numbers.begin(), numbers.end(), 1);

    // Use parallel transform_reduce to sum the values in parallel
    int sum = std::transform_reduce(
        std::execution::par, // parallel execution policy parallel or std::execution::seq for sequential
        numbers.begin(),
        numbers.end(),
        0,                      // initial value
        std::plus<int>{},       // binary operation to combine results
        [](int v) { return v; } // unary operation to transform each element
    );
    std::cout << "Sum of numbers from 1 to 100: " << sum << '\n';

    return 0;
}
