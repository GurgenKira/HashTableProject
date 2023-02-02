// Headers from this project
#include "separate_chaining_hash_table.hpp"

// Headers from standard libraries
#include <iostream>
#include <string>
#include <cassert>

/// This is the entry point of the program, the main function
int main()
{
        hash_table::separate_chaining_hash_table<int, std::string> mymap;
        mymap.insert({1, "AAA"});
        mymap.insert({2, "BBB"});
        mymap.insert({3, "CCC"});
        std::cout << mymap[3] << std::endl;
        std::cout << mymap[2] << std::endl;
        assert(mymap.erase(2));
        assert(mymap.get_size() == 2);
        assert(!mymap.find(2));
        assert(mymap.find(1));
        return 0;
}
