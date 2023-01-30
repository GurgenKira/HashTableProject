#ifndef HASH_TABLE_ITERATOR_HPP
#define HASH_TABLE_ITERATOR_HPP

#include <vector>

namespace hash_table {

template <typename separate_chaining_hash_table>
class hash_table_iterator 
{
public:
        using value_type     = typename separate_chaining_hash_table::value_type;
        using bucket_type    = typename separate_chaining_hash_table::bucket_type; 
        using pointer_type   = value_type*;
        using reference_type = value_type&;
public: 
        
        /// constructor․
        hash_table_iterator(typename std::vector<bucket_type>::iterator it) : m_it{it} {} 

        /// prefix operator++
        hash_table_iterator& operator++();
        
        /// postfix operator++
        hash_table_iterator operator++(int);
        
        /// operator->
        pointer_type operator->();
        
        /// operator*
        reference_type operator*();

        /// operator==
        //friend bool operator== (const iterator& a, const iterator& b);
        
        /// operator!=
        //friend bool operator!= (const Iterator& a, const Iterator& b);

private:
        typename std::vector<bucket_type>::iterator m_it;
}; // class hash_table_iterator


} // namespace hash_table

#include "hash_table_iterator.cpp"

#endif // HASH_TABLE_ITERATOR_HPP
