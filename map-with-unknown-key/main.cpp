/**
What happens if you access an unknown key in the std::map, std::unordered_map?
*/
#include <iostream>
#include <map>
#include <string>
#include <format>
#include <print>

int
main()
{
    std::map<std::string, int> my_map;
    std::print("Accessing unknown key 'unknown_key' in std::map:\n");
    int value = my_map["unknown_key"];
    std::print("Value: {}\n", value);                         // Should print 0, as default-constructed int is 0
    std::print("Map size after access: {}\n", my_map.size()); // Should print 1
    return 0;
}
