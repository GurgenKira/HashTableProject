#ifndef SEPARATE_CHAINING_HASH_TABLE_HPP
#define SEPARATE_CHAINING_HASH_TABLE_HPP

// Headers from this project
#include "hash_table_iterator.hpp"

// Headers from standard libraries
#include <algorithm>
#include <functional>
#include <list>
#include <utility>
#include <vector>
#include <set>
#include <iostream>

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
        using value_type        = std::pair<Key, Value>;
        using bucket_type       = std::list<value_type>;
        using table_type        = std::vector<bucket_type>;
        using size_type         = std::size_t;
        using iterator_type     = hash_table_iterator<separate_chaining_hash_table<Key,
                                                                             Value,
                                                                             Hash,
                                                                             KeyEqual>>;
        using insert_return_type = std::pair<iterator_type, bool>;

public:
        /// default constructor․
        separate_chaining_hash_table();

        /// destructor․
        ~separate_chaining_hash_table();

        /// Copy constructor.
        separate_chaining_hash_table(const separate_chaining_hash_table& o);

        /// Move constructor.
        separate_chaining_hash_table(separate_chaining_hash_table&& o) noexcept;

        /// Copy assignment operator.
        separate_chaining_hash_table& operator=(const separate_chaining_hash_table& o); 

        /// Move assignment operator.
        separate_chaining_hash_table& operator=(separate_chaining_hash_table&& o);
public:
       /**
        * @brief inserts the given value into the hash table.
        * @param e the value to be inserted into the table is represented by a pair.
        * @return pair of iterator and logic value(true if insertion succesed otherwise false).
        */
        insert_return_type insert(const value_type& e);
        
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
        Value operator[](const Key& k);

        /// returns the number of buckets in the table.
        size_type get_table_size() const noexcept { return m_table.size(); }
       
        /// returns the number of elements in the table. 
        size_type get_size() const noexcept { return m_size; }
       
        /// returns a number corresponding to the division of elements in the table and buckets. 
        double load_factor() const;
       
       /**
        * @brief returns an iterator to the first element of the separate_chaining_hash_table.
        * @return iterator to the first element.
        */
        iterator_type begin() { return iterator_type(); }
        
       /**
        * @brief returns an iterator to the element following the last element of the separate_chaining_hash_table.
        * @return iterator to the element following the last element.
        */
        iterator_type end() 
        {
                std::cout << __func__ << std::endl; 
                return iterator_type(m_table[get_table_size()]); 
        }
        
private:
        // heleper functions
        size_type find_the_key_index(const Key&);
        bool key_exists_in_bucket(const Key&, const bucket_type&);
        void rehash();
private:
        table_type   m_table;
        size_type    m_size;
        static constexpr inline size_type m_table_default_size = 20;
}; // class separate_chaining_hash_table

} // namespace hash_table

// It's not considered good practice to do this, 
// but it makes the class interface cleaner 
// and allows you to split the template class into files. 
#include "separate_chaining_hash_table.cpp"

#endif // SEPARATE_CHAINING_HASH_TABLE_HPP
