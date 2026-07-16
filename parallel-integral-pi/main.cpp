/*
    pi = \int 0^1 \frac{4}{1+x^2} dx    
    this demo computes pi using the trapezoidal rule in parallel aka. multithreaded
*/

#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>

double f(double x)
{
    return 4.0 / (1.0 + x * x);
}

int
main(int argc, char* argv[])
{
    long long iterations = 10000000000;
    if (argc > 1) {
        iterations = std::atoll(argv[1]);
    }
    int threads = 10;
    if (argc > 2) {
        threads = std::atoi(argv[2]);
    }

    // compute the width of each trapezoid
    double h = 1.0 / static_cast<double>(iterations);
    // compute the area of each trapezoid in parallel
    double sum = 0.0;
    // create a vector of threads
    std::vector<std::thread> thread_pool;
    // create a vector of partial sums
    std::vector<double> partial_sums(threads, 0.0);
    for (int t = 0; t < threads; ++t) {
        thread_pool.emplace_back([&, t]() {
            long long start = t * (iterations / threads);
            long long end = (t + 1) * (iterations / threads);
            for (long long i = start; i < end; ++i) {
                double x = h * static_cast<double>(i);
                partial_sums[t] += f(x);
            }
        });
    }
    // join the threads
    for (auto& thread : thread_pool) {
        thread.join();
    }
    // sum the partial sums
    for (int t = 0; t < threads; ++t) {
        // std::cout << "partial sum from thread " << t << " = " << partial_sums[t] << std::endl;
        sum += partial_sums[t];
    }
    // multiply by the width of each trapezoid to get the final result
    double pi = h * sum;
    // set precision and print the result
    std::cout.precision(15);
    std::cout << "pi = " << pi << std::endl;
}