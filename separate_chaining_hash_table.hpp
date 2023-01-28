#ifndef SEPARATE_CHAINING_HASH_TABLE
#define SEPARATE_CHAINING_HASH_TABLE

// Headers from standard libraries
#include <algorithm>
#include <functional>
#include <list>
#include <utility>
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

        /// Copy constructor.
        separate_chaining_hash_table(const separate_chaining_hash_table& o);

        /// Move constructor.
        separate_chaining_hash_table(separate_chaining_hash_table&& o);

        /// Copy assignment operator.
        separate_chaining_hash_table& operator=(const separate_chaining_hash_table& o); 

        /// Move assignment operator.
        separate_chaining_hash_table& operator=(separate_chaining_hash_table&& o);
public:
       /**
        * @brief inserts the given value into the hash table.
        * @param e the value to be inserted into the table is represented by a pair.
        * @return true if insertion succesed otherwise false.
        */
        //TODO:/ make return value pair
        bool insert(const value_type& e);
        
       /**
        * @brief deletes the element with the given key from the table. 
        * @param k The key of the element to be deleted․
        * @return Number of elements removed (0 or 1).
        */
        size_type erase(const Key& k);
       
       /**
        * @brief finds an element with key equivalent to key.
        * @param k key value of the element to search for.
        * @return true if element exists otherwise false.
        */
        bool find(const Key& k);

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
