// Headers from this project
#include "separate_chaining_hash_table.hpp"

// Headers from standard libraries
#include <iostream>
#include <string>

/// This is the entry point of the program, the main function
int main()
{
        hash_table::separate_chaining_hash_table<int, std::string> table;
        table.insert({0, "AAA"});
        table.insert({1, "BBB"});
        table.insert({2, "CCC"});
        std::cout << table.get_size() << std::endl;
        std::cout << "table[0] : " << table[0] << std::endl;
        std::cout << "table[1] : " << table[1] << std::endl;
        table[0] = "LLL";
        std::cout << "table[0] : " << table[0] << std::endl;
        table[0] = "PPP";
        std::cout << "table[1] : " << table[1] << std::endl;
        return 0;
}
