#ifdef SEPARATE_CHAINING_HASH_TABLE

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
void 
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
insert(const value_type& e)
{
        size_type index = find_the_key_index(e.first);
        bucket_type& bucket = m_table[index];
        bucket.push_front(std::move(e));
        ++m_size;
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
Value& 
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
operator[](const Key& k)
{
        size_type index = find_the_key_index(k);
        bucket_type backet = m_table[index];
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
typename separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::size_type 
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
find_the_key_index(const Key& k)
{
        return Hash()(k) % get_table_size();         
}

} // namespace hash_table

#endif // SEPARATE_CHAINING_HASH_TABLE
