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
        separate_chaining_hash_table()
                : m_size{0}
                , m_table{}
        {
                m_table.resize(m_table_default_size);
        }
        
        ~separate_chaining_hash_table() 
        {
                
        }
public:
        void insert(const value_type& e)
        {
                size_type index = find_the_key_index(e.first);
                bucket_type& bucket = m_table[index];
                bucket.push_front(std::move(e));
                ++m_size;
        }
        
        Value& operator[](const Key& k)
        {
                size_type index = find_the_key_index(k);
                bucket_type backet = m_table[index];
                auto it = std::find_if(std::begin(backet), std::end(backet),
                                [&](const value_type& v) { return v.first ==  k; } ); 
                return (*it).second; 
        }

        size_type get_table_size() const noexcept
        {
                return m_table.size();
        }
        
        size_type get_size() const noexcept
        {
                return m_size;
        }

private:
        size_type find_the_key_index(const Key& k)
        {
                return Hash()(k) % table_size();         
        }

private:
        table_type m_table;
        size_type  m_size;
        static constexpr inline size_type m_table_default_size = 20;
}; // class separate_chaining_hash_table

} //hash_table

#endif // SEPARATE_CHAINING_HASH_TABLE


