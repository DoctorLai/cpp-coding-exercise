#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

double
f(double x)
{
    return 4.0 / (1.0 + x * x);
}

int
main(int argc, char* argv[])
{
    long long iterations = 1000000;
    if (argc > 1) {
        iterations = std::atoll(argv[1]);
    }
    int threads = 10;
    if (argc > 2) {
        threads = std::atoi(argv[2]);
    }

    if (iterations <= 0 || threads <= 0) {
        std::cerr << "iterations and threads must be positive integers\n";
        return 1;
    }

    const double h = 1.0 / static_cast<double>(iterations);
    const long long interior_points = iterations - 1;
    const int worker_count = static_cast<int>(std::min<long long>(threads, iterations));
    const long long points_per_thread = interior_points / worker_count;
    const long long remainder = interior_points % worker_count;

    std::vector<std::thread> thread_pool;
    thread_pool.reserve(worker_count);
    std::vector<double> partial_sums(worker_count, 0.0);

    for (int t = 0; t < worker_count; ++t) {
        thread_pool.emplace_back([&, t]() {
            const long long thread_index = t;
            const long long start = 1 + thread_index * points_per_thread + std::min(thread_index, remainder);
            const long long end = start + points_per_thread + (thread_index < remainder ? 1 : 0);

            double local_sum = 0.0;
            for (long long i = start; i < end; ++i) {
                const double x = h * static_cast<double>(i);
                local_sum += 2.0 * f(x);
            }
            partial_sums[t] = local_sum;
        });
    }

    for (auto& thread : thread_pool) {
        thread.join();
    }

    // T_n = (h / 2) * (f(0) + f(1) + 2 * sum of interior points).
    double sum = f(0.0) + f(1.0);
    for (const double partial_sum : partial_sums) {
        sum += partial_sum;
    }

    const double pi = (h / 2.0) * sum;
    std::cout.precision(15);
    std::cout << "pi = " << pi << '\n';
}