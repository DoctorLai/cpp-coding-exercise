/**
 * This program implements various algorithms for integer factorization,
 * It takes integer(s) from the command line or a file and outputs their prime
 * factorizations.
 *
 * Usage:
 *   ./integer-factorization [options] [integers...]
 * Options:
 *   -h, --help          Show this help message and exit
 *   -f, --file FILE     Read integers from FILE, one per line
 *   -o, --output FILE    Write output to FILE instead of stdout
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <getopt.h>
#include "factorization_algorithms.hpp"

void
print_help()
{
    std::cout << "Usage: ./integer-factorization [options] [integers...]\n"
              << "Options:\n"
              << "  -h, --help          Show this help message and exit\n"
              << "  -f, --file FILE     Read integers from FILE, one per line\n"
              << "  -o, --output FILE    Write output to FILE instead of stdout\n";
}

int
main(int argc, char* argv[])
{
    std::string input_file;
    std::string output_file;
    std::vector<long long> numbers;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"file", required_argument, 0, 'f'},
        {"output", required_argument, 0, 'o'},
        {0, 0, 0, 0}};

    int opt;
    while ((opt = getopt_long(argc, argv, "hf:o:", long_options, NULL)) != -1) {
        switch (opt) {
        case 'h':
            print_help();
            return 0;
        case 'f':
            input_file = optarg;
            break;
        case 'o':
            output_file = optarg;
            break;
        default:
            print_help();
            return 1;
        }
    }

    // Read numbers from file if specified
    if (!input_file.empty()) {
        std::ifstream infile(input_file);
        long long num;
        while (infile >> num) {
            numbers.push_back(num);
        }
    }

    // Read numbers from command line arguments
    for (int index = optind; index < argc; index++) {
        numbers.push_back(std::stoll(argv[index]));
    }

    // Prepare output stream
    std::ostream* out_stream = &std::cout;
    std::ofstream outfile;
    if (!output_file.empty()) {
        outfile.open(output_file);
        out_stream = &outfile;
    }

    // Factor each number and output the result
    for (const auto& number : numbers) {
        std::vector<long long> factors;
        factors = trial_division(number);
        *out_stream << "Factors of " << number << ": ";
        for (const auto& factor : factors) {
            *out_stream << factor << " ";
        }
        *out_stream << "\n";
    }
    if (outfile.is_open()) {
        outfile.close();
    }
    return 0;
}
