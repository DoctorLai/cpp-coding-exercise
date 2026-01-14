/**
What happens if you access an unknown key in the std::map, std::unordered_map?
*/
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <print>
#include <cassert>

int
main()
{
    // Example with std::map value type int
    std::map<std::string, int> my_map;
    std::print("Accessing unknown key 'unknown_key' in std::map:\n");
    int value = my_map["unknown_key"];
    std::print("Value: {}\n", value);                         // Should print 0, as default-constructed int is 0
    std::print("Map size after access: {}\n", my_map.size()); // Should print 1
    assert(value == 0);                                       // Default-constructed int is 0
    assert(my_map.size() == 1);                               // The map now contains one entry for 'unknown_key'

    // Example with std::unordered_map value type int
    std::unordered_map<std::string, int> my_unordered_map;
    std::print("Accessing unknown key 'unknown_key' in std::unordered_map:\n");
    int unordered_value = my_unordered_map["unknown_key"];
    std::print("Value: {}\n", unordered_value);                                   // Should print 0
    std::print("Unordered map size after access: {}\n", my_unordered_map.size()); // Should print 1
    assert(unordered_value == 0);                                                 // Default-constructed int is 0
    assert(my_unordered_map.size() == 1); // The unordered_map now contains one entry for 'unknown_key'

    // Example with std::map value type std::string
    std::map<std::string, std::string> my_string_map;
    std::print("Accessing unknown key 'unknown_key' in std::map with string values:\n");
    std::string str_value = my_string_map["unknown_key"];
    std::print("Value: '{}'\n", str_value);                          // Should print empty string
    std::print("Map size after access: {}\n", my_string_map.size()); // Should print 1
    assert(str_value.empty());                                       // Default-constructed string is empty
    assert(my_string_map.size() == 1);                               // The map now contains one entry for

    // Example with std::unordered_map value type std::string
    std::unordered_map<std::string, std::string> my_string_unordered_map;
    std::print("Accessing unknown key 'unknown_key' in std::unordered_map with string values:\n");
    std::string str_unordered_value = my_string_unordered_map["unknown_key"];
    std::print("Value: '{}'\n", str_unordered_value);                                    // Should print empty string
    std::print("Unordered map size after access: {}\n", my_string_unordered_map.size()); // Should print 1
    assert(str_unordered_value.empty());         // Default-constructed string is empty
    assert(my_string_unordered_map.size() == 1); // The unordered_map now contains one entry for 'unknown_key'
    return 0;
}
