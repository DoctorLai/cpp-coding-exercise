#include "factorization_algorithms.hpp"

std::vector<long long>
trial_division(long long n)
{
    std::vector<long long> factors;
    for (long long i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }
    return factors;
}
