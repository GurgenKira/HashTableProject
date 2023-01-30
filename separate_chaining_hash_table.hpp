#ifndef SEPARATE_CHAINING_HASH_TABLE_HPP
#define SEPARATE_CHAINING_HASH_TABLE_HPP

// Headers from this project
#include "hash_table_iterator.hpp"

// Headers from standard libraries
#include <algorithm>
#include <functional>
#include <forward_list>
#include <utility>
#include <vector>
#include <set>
#include <iostream>
#include <shared_mutex>

namespace hash_table {

template<
        typename Key,
        typename Value,
        typename Hash = std::hash<Key>,
        typename KeyEqual = std::equal_to<Key>
>
class separate_chaining_hash_table 
{
        enum { table_default_size = 1 };
public:
        using value_type        = std::pair<Key, Value>;
        using bucket_type       = std::forward_list<value_type>;
        using table_type        = std::vector<bucket_type>;
        using size_type         = std::size_t;
        using iterator_type     = hash_table_iterator<separate_chaining_hash_table<Key,
                                                                             Value,
                                                                             Hash,
                                                                             KeyEqual>>;
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
        * @return true if insertion succesed otherwise false.
        */
        bool insert(const value_type& e);
        
       /**
        * @brief deletes the element with the given key from the table. 
        * @param k The key of the element to be deleted․
        * @return true if erase succesed otherwise false.
        */
        bool erase(const Key& k);
       
       /**
        * @brief finds an element with key equivalent to key.
        * @param k key value of the element to search for.
        * @return true if element exists otherwise false.
        */
        bool find(const Key& k) const;

       /**
        * @brief to access an element with a given key.
        * @param k the key to access the value of the element.
        * @return reference to the value of the element with the given key․
        */
        const Value& operator[](const Key& k);

        /// returns the number of buckets in the table.
        size_type get_table_size() const noexcept 
        { 
                std::shared_lock<std::shared_mutex> lock(m_mutex);
                return m_table.size(); 
        }
       
        /// returns the number of elements in the table. 
        size_type get_size() const noexcept 
        { 
                std::shared_lock<std::shared_mutex> lock(m_mutex);
                return m_size; 
        }
       
        /// returns a number corresponding to the division of elements in the table and buckets. 
        double load_factor() const;
       
       /**
        * @brief returns an iterator to the first element of the separate_chaining_hash_table.
        * @return iterator to the first element.
        */
        iterator_type begin() 
        { 
                std::shared_lock<std::shared_mutex> lock(m_mutex);
                return iterator_type(m_table.begin()); 
        }
        
       /**
        * @brief returns an iterator to the element following the last element of the separate_chaining_hash_table.
        * @return iterator to the element following the last element.
        */
        iterator_type end() 
        {
                std::shared_lock<std::shared_mutex> lock(m_mutex);
                return iterator_type(m_table.end()); 
        }
        
private:
        // heleper functions
        size_type find_the_key_index(const Key&) const;
        bool key_exists_in_bucket(const Key&, const bucket_type&) const;

        void rehash();
private:
        table_type   m_table;
        size_type    m_size;
        mutable std::shared_mutex m_mutex;
}; // class separate_chaining_hash_table

} // namespace hash_table

// It's not considered good practice to do this, 
// but it makes the class interface cleaner 
// and allows you to split the template class into files. 
#include "separate_chaining_hash_table.cpp"

#endif // SEPARATE_CHAINING_HASH_TABLE_HPP
