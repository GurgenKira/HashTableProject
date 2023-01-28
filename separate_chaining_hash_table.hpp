#ifndef SEPARATE_CHAINING_HASH_TABLE
#define SEPARATE_CHAINING_HASH_TABLE

// Headers from standard libraries
#include <functional>
#include <utility>
#include <list>
#include <vector>

namespace hash_table {

template<
        typename Key,
        typename Value,
        typename Hash = std::hash<Key>,
        typename KeyEqual = std::equal_to<Key>
>
class separate_chaining_hash_table 
{
public:
        using value_type  = std::pair<const Key, Value>;
        using bucket_type = std::list<value_type>;
        using table_type  = std::vector<bucket_type>;
        using size_type   = std::size_t;
public:
        /// default constructor․
        separate_chaining_hash_table();
        /// destructor․
        ~separate_chaining_hash_table(); 
public:
       /**
        * @brief inserts the given value into the hash table.
        * @param e the value to be inserted into the table is represented by a pair.
        */
        void insert(const value_type& e);
        
       /**
        * @brief to access an element with a given key, and create it if the element does not exist.
        * @param k the key to access the value of the element.
        * @return reference to the value of the element with the given key․
        */
        Value& operator[](const Key& k);

        /// returns the number of buckets in the table.
        size_type get_table_size() const noexcept { return m_table.size(); }
        
        /// returns the number of elements in the table. 
        size_type get_size() const noexcept { return m_size; }

private:
        // heleper functions
        size_type find_the_key_index(const Key&);
private:
        table_type m_table;
        size_type  m_size;
        static constexpr inline size_type m_table_default_size = 20;
}; // class separate_chaining_hash_table

} // namespace hash_table

// It's not considered good practice to do this, 
// but it makes the class interface cleaner 
// and allows you to split the template class into files. 
#include "separate_chaining_hash_table.cpp"

#endif // SEPARATE_CHAINING_HASH_TABLE
