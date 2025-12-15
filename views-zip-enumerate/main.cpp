#include <iostream>
#include <string>
#include <ranges>

void
enumerate(std::string_view str)
{
    for (const auto& [index, character] : std::views::zip(std::views::iota(0), str)) {
        std::cout << index << ": " << character << '\n';
    }
}

int
main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <string1> <string2> ...\n";
        enumerate("default string");
        // make pipeline happy
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        std::string_view input = argv[i];
        std::cout << "Enumerating string: " << input << '\n';
        enumerate(input);
        std::cout << "------------------------\n";
    }
    return 0;
}
