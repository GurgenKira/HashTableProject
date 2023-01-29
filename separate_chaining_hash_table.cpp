#ifdef SEPARATE_CHAINING_HASH_TABLE_HPP

#include <iostream>

namespace hash_table {

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
separate_chaining_hash_table()
        : m_size{0}
        , m_table{}
{
        m_table.resize(m_table_default_size);
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
~separate_chaining_hash_table()
{
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
separate_chaining_hash_table(const separate_chaining_hash_table& o)
        : m_table(o.m_table)
        , m_size(o.m_size) 
{
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
separate_chaining_hash_table(separate_chaining_hash_table&& o) noexcept
        : m_table{std::move(o.m_table)}
        , m_size{std::move(o.m_size)}
{
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>& 
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
operator=(const separate_chaining_hash_table& o)
{
        if (this != &o) {
                // clear
                m_table = o.m_table;
                m_size = o.m_size;
        }
        return *this;
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>& 
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
operator=(separate_chaining_hash_table&& o)
{
        if (this != &o) {
                // clear
                m_table = std::move(o.m_table);
                m_size = std::move(o.m_size);
        }
        return *this;
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
typename separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::insert_return_type
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
insert(const value_type& e)
{
        if (load_factor() > 0.7) {
                rehash();
        }
        const size_type index = find_the_key_index(e.first);
        bucket_type& bucket = m_table[index];
        if (key_exists_in_bucket(e.first, bucket)) {
                return std::make_pair(end(), false);
        }
        bucket.push_front(std::move(e));
        ++m_size;
        return std::make_pair(iterator_type(bucket), true);
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
typename separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::size_type 
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
erase(const Key& k)
{
        const size_type index = find_the_key_index(k);
        bucket_type& bucket = m_table[index];
        if (bucket.empty()) {
                return 0;
        }
        auto ri = std::remove_if(std::begin(bucket), std::end(bucket),
                                [&](const value_type& v)
                                {
                                        return v.first == k;
                                });
        if (ri == std::end(bucket)) {
                return 0;
        }
        bucket.erase(ri);
        --m_size;
        return 1;
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
bool 
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
find(const Key& k)
{
        const size_type index = find_the_key_index(k);
        const bucket_type& bucket = m_table[index];
        return key_exists_in_bucket(k, bucket); 
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
Value 
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
operator[](const Key& k)
{
        const size_type index = find_the_key_index(k);
        const bucket_type& backet = m_table[index];
        auto it = std::find_if(std::begin(backet), std::end(backet),
                        [&](const value_type& v) { return v.first ==  k; } ); 
        return (*it).second; 
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
double 
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
load_factor() const
{
        return get_size() / static_cast<double>(get_table_size());
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
typename separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::size_type 
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
find_the_key_index(const Key& k)
{
        return Hash()(k) % get_table_size();         
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
bool 
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
key_exists_in_bucket(const Key& k, const bucket_type& b)
{
        return std::find_if(std::begin(b), std::end(b), 
                                        [&](const value_type& v) 
                                        {
                                                return v.first == k; 
                                        }) != std::end(b); 
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
void 
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
rehash()
{
        const size_type nst = get_table_size() * 2; 
        table_type new_table(nst);
        for (bucket_type& bac : m_table) {
                for (value_type& elem : bac) {
                        size_type hash  = Hash()(elem.first);
                        size_type index = hash % nst;
                        new_table[index].push_front(std::move(elem));
                }
        }
        m_table.swap(new_table);
}

} // namespace hash_table

#endif // SEPARATE_CHAINING_HASH_TABLE_HPP
