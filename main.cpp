// Headers from this project
#include "separate_chaining_hash_table.hpp"

// Headers from standard libraries
#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>

/// This is the entry point of the program, the main function
int main()
{
        //std::unordered_map<int, std::string> t;
        //t.insert({0, "AAA"});
        //t.insert({1, "BBB"});
        //t.insert({2, "CCC"});
        //t.insert({3, "DDD"});
        //t.insert({4, "EEE"});
        //t.insert({5, "FFF"});
        //t.insert({6, "III"});
        //auto it = t.begin();
        //std::cout << (*it).first << std::endl;
        // ++it;
        // it++;
        //std::cout << it->second << std::endl;
        hash_table::separate_chaining_hash_table<int, std::string> table;
        
        table.insert({0, "AAA"});
        table.insert({1, "BBB"});
        table.insert({2, "CCC"});
        table.insert({3, "DDD"});
        std::cout << table[3] << std::endl;
        table.erase(3);

        //std::cout << table[3] << std::endl;
        // auto it = table.insert({3, "DDD"}).first;
        //std::cout << table.find(3) << std::endl;
        //std::cout << table.find(2) << std::endl;
        //std::cout << table.find(1) << std::endl;
        //std::cout << table.find(4) << std::endl;
        return 0;
}
