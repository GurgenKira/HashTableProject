// Headers from this project
#include "raii_timer.hpp"
#include "../separate_chaining_hash_table.hpp"

// Headers from standard libraries
#include <cassert>

#include <iostream>
#include <vector>
#include <unordered_map>

int operation_count = 10000;

// user define class to use as a key
struct Point 
{
        Point(int x, int y)
                : m_x{x}
                , m_y{y}
        {}
        
        friend bool operator==(const Point& p1, const Point& p2)
        {
                return (p1.m_x == p2.m_x) && (p1.m_y == p2.m_y);
        }
        
        int m_x;
        int m_y;

}; // class Point

namespace std
{
    template <>
    struct hash<Point>
    {
    public:
        size_t operator()(const Point& p) const
        {
                return hash<int>()(p.m_x) ^ hash<int>()(p.m_y);
        }
    };
} // namespace std

void test_insert(std::unordered_map<Point, std::string>& map)
{
        timer::raii_time_and_log rtl;
        for (int i = 0; i < operation_count; ++i) {
                map.insert({Point(i, i), "AAA"});
        }
        assert(map.size() == operation_count);
        std::cout << "std::unordered_map insert operation take : ";
}

void test_insert(hash_table::separate_chaining_hash_table<Point, std::string>& map)
{
        timer::raii_time_and_log rtl;
        for (int i = 0; i < operation_count; ++i) {
                map.insert({Point(i, i), "AAA"});
        }
        assert(map.get_size() == operation_count);
        std::cout << "hash_table::separate_chaining_hash_table insert operation take : ";
}

void test_find(std::unordered_map<Point, std::string>& map)
{
        timer::raii_time_and_log rtl;
        for (int i = 0; i < operation_count; ++i) {
                assert(map.find(Point(i, i)) != std::end(map));
        }
        std::cout << "std::unordered_map find operation take : ";
}

void test_find(hash_table::separate_chaining_hash_table<Point, std::string>& map)
{
        timer::raii_time_and_log rtl;
        for (int i = 0; i < operation_count; ++i) {
                assert(map.find(Point(i, i)));
        }
        std::cout << "hash_table::separate_chaining_hash_table find operation take : ";
}

void test_erase(std::unordered_map<Point, std::string>& map)
{
        timer::raii_time_and_log rtl;
        for (int i = 0; i < operation_count; ++i) {
                assert(map.erase(Point(i, i)) != 0);
        }
        assert(map.size() == 0);
        std::cout << "std::unordered_map erase operation take : ";
}

void test_erase(hash_table::separate_chaining_hash_table<Point, std::string>& map)
{
        timer::raii_time_and_log rtl;
        for (int i = 0; i < operation_count; ++i) {
                assert(map.erase(Point(i, i)));
        }
        assert(map.get_size() == 0);
        std::cout << "hash_table::separate_chaining_hash_table erase operation take : ";
}

int main()
{
        std::unordered_map<Point, std::string> stdmap;
        hash_table::separate_chaining_hash_table<Point, std::string> mymap;
        test_insert(stdmap);
        test_insert(mymap);
        test_find(stdmap);
        test_find(mymap);
        test_erase(stdmap);
        test_erase(mymap);
        return 0; 
}
