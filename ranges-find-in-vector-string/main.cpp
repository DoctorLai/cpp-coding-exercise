/**
This demonstrates different ways to find an element in a vector of strings
*/
#include <iostream>
#include <vector>
#include <string>
#include <print>
#include <cassert>
#include <ranges>
#include <algorithm>

int
main()
{
    std::vector<std::string> vec = {"apple", "banana", "cherry", "date", "elderberry"};
    std::string target = "cherry";

    // Method 1: Using a loop
    bool found = false;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) {
            std::print("loop: Found '{}' using loop at index {}\n", target, i);
            found = true;
            break;
        }
    }
    if (!found) {
        std::print("loop: '{}' not found using loop\n", target);
    }

    // Method 2: Using std::find_if with a lambda
    auto it_if = std::find_if(vec.begin(), vec.end(), [&target](const std::string& s) { return s == target; });
    if (it_if != vec.end()) {
        std::print(
            "std::find_if: Found '{}' using std::find_if at index {}\n", target, std::distance(vec.begin(), it_if));
    } else {
        std::print("std::find_if: '{}' not found using std::find_if\n", target);
    }

    // Method 3: Using std::find
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {
        std::print("std::find: Found '{}' using std::find at index {}\n", target, std::distance(vec.begin(), it));
    } else {
        std::print("std::find: '{}' not found using std::find\n", target);
    }

    // Method 4: std::count (pre C++20)
    auto count_std = std::count(vec.begin(), vec.end(), target);
    std::print("std::count: Vector contains '{}' {} time(s) using std::count\n", target, count_std);

    // Method 5: std::count_if (pre C++20)
    auto count_if_std = std::count_if(vec.begin(), vec.end(), [&target](const std::string& s) { return s == target; });
    std::print("std::count_if: Vector contains '{}' {} time(s) using std::count_if\n", target, count_if_std);

    // Method 6: std::any_of
    bool any_of_std = std::any_of(vec.begin(), vec.end(), [&target](const std::string& s) { return s == target; });
    if (any_of_std) {
        std::print("std::any_of: Vector contains '{}' using std::any_of\n", target);
    } else {
        std::print("std::any_of: Vector does not contain '{}' using std::any_of\n", target);
    }

    // Method 7: Using std::ranges::find (C++20)
    auto range_it = std::ranges::find(vec, target);
    if (range_it != vec.end()) {
        std::print(
            "std::ranges::find: Found '{}' using std::ranges::find at index {}\n",
            target,
            std::distance(vec.begin(), range_it));
    } else {
        std::print("std::ranges::find: '{}' not found using std::ranges::find\n", target);
    }

    // Method 8: Using std::ranges::find_if with a lambda (C++20)
    auto range_it_if = std::ranges::find_if(vec, [&target](const std::string& s) { return s == target; });
    if (range_it_if != vec.end()) {
        std::print(
            "std::ranges::find_if: Found '{}' using std::ranges::find_if at index {}\n",
            target,
            std::distance(vec.begin(), range_it_if));
    } else {
        std::print("std::ranges::find_if: '{}' not found using std::ranges::find_if\n", target);
    }

    // Method 9: std::ranges::contains (C++23)
    auto contains = std::ranges::contains(vec, target);
    if (contains) {
        std::print("std::ranges::contains: Vector contains '{}' using std::ranges::contains\n", target);
    } else {
        std::print("std::ranges::contains: Vector does not contain '{}' using std::ranges::contains\n", target);
    }

    // Method 10: std::ranges::any_of (C++20)
    bool any_of = std::ranges::any_of(vec, [&target](const std::string& s) { return s == target; });
    if (any_of) {
        std::print("std::ranges::any_of: Vector contains '{}' using std::ranges::any_of\n", target);
    } else {
        std::print("std::ranges::any_of: Vector does not contain '{}' using std::ranges::any_of\n", target);
    }

    // Method 11: std::ranges::count (C++20)
    auto count = std::ranges::count(vec, target);
    std::print("std::ranges::count: Vector contains '{}' {} time(s) using std::ranges::count\n", target, count);

    // Method 12: std::ranges::count_if (C++20)
    auto count_if = std::ranges::count_if(vec, [&target](const std::string& s) { return s == target; });
    std::print(
        "std::ranges::count_if: Vector contains '{}' {} time(s) using std::ranges::count_if\n", target, count_if);

    // Method 13: via std::ranges::views (C++20)
    auto view = vec | std::ranges::views::filter([&target](const std::string& s) { return s == target; });
    for (const auto& s : view) {
        std::print("std::ranges::views::filter: Found '{}' using std::ranges::views::filter\n", s);
    }

    // Assertions to verify correctness
    assert(it != vec.end() && *it == target);
    assert(found);
    assert(range_it != vec.end() && *range_it == target);
    assert(it_if != vec.end() && *it_if == target);
    assert(range_it_if != vec.end() && *range_it_if == target);
    assert(contains);
    assert(any_of);
    assert(count == 1);
    assert(count_std == 1);
    assert(count_if == 1);
    assert(count_if_std == 1);
    assert(std::ranges::distance(view) == 1);
    assert(any_of_std);

    return 0;
}
