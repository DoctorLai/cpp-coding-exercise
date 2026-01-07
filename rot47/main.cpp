#include <iostream>
#include <string>
#include <string_view>
#include <ranges>

[[nodiscard]]
std::string
rot47(std::string_view input)
{
    auto transform = [](char c) { return (c >= 33 && c <= 126) ? static_cast<char>(33 + ((c - 33 + 47) % 94)) : c; };

    std::string output;
    output.reserve(input.size());

    for (char c : input | std::views::transform(transform)) {
        output.push_back(c);
    }

    return output;
}

int
main(int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i) {
        std::cout << rot47(argv[i]);

        if (i + 1 < argc) {
            std::cout << ' ';
        }
    }
}
