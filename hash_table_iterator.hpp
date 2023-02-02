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
        using reference_type = bucket_type&;
public: 
        
        /// constructor․
        hash_table_iterator(typename std::vector<bucket_type>::iterator it)
                : m_table_it{it}
        {} 

        /// prefix operator++
        hash_table_iterator& operator++()
        {
                m_table_it++;
                return *this;
        }
        
        /// postfix operator++
        hash_table_iterator operator++(int)
        {
                hash_table_iterator<separate_chaining_hash_table> old_value(*this);
                 ++(*this);
                return old_value;
        }

        /// operator*
        // TODO
        reference_type operator*()
        {
                return m_table_it;   
        }

        /// operator==
        friend bool operator==(const hash_table_iterator& a, const hash_table_iterator& b)
        {
                return a.m_table_it == b.m_table_it;
        }
        
        /// operator!=
        friend bool operator!=(const hash_table_iterator& a, const hash_table_iterator& b)
        {
                return !(a == b);
        }

private:
        typename std::vector<bucket_type>::iterator m_table_it;
}; // class hash_table_iterator


} // namespace hash_table

#include "hash_table_iterator.cpp"

#endif // HASH_TABLE_ITERATOR_HPP
