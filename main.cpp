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
        assert(mymap[3] == "CCC");
        assert(mymap[2] == "BBB");
        assert(mymap.get_size() == 3);
        assert(mymap.find(1));
        for (auto it : mymap) {
                std::cout << "it.first : " << it.first << " : it.second : " << it.second << std::endl;
        }
        for (auto it = mymap.begin(); it != mymap.end(); ++it) {
                std::cout << "(*it).first : " << (*it).first << " : (*it).second : " << (*it).second << std::endl;
        }
        assert(mymap.erase(3));
        assert(!mymap.find(3));
        return 0;
}
