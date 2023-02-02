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
        : m_table{}
        , m_size(0)
{
        m_table.resize(table_default_size);
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
        m_table.clear();
        m_size = 0;
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
separate_chaining_hash_table(const separate_chaining_hash_table& o)
{
        std::unique_lock<std::shared_mutex> lock(o.m_mutex);
        m_table = o.m_table;
        m_size = o.m_size;
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
separate_chaining_hash_table(separate_chaining_hash_table&& o) noexcept
{
        std::unique_lock<std::shared_mutex> lock(o.m_mutex);
        m_table = std::move(o.m_table);
        m_size = std::move(o.m_size);
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
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        std::unique_lock<std::shared_mutex> lock2(o.m_mutex);
        if (this != &o) {
                m_table.clear();
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
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        std::unique_lock<std::shared_mutex> lock2(o.m_mutex);
        if (this != &o) {
                m_table.clear();
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
bool
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
insert(const value_type& e)
{
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        if (load_factor() > 0.7) {
                rehash();
        }
        const size_type index = find_the_key_index(e.first);
        bucket_type& bucket = m_table[index];
        if (find_key_in_bucket(e.first, bucket) != std::end(bucket)) {
                return false;
        }
        bucket.push_front(std::move(e));
        ++m_size;
        return true;
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
bool
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
erase(const Key& k)
{
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        const size_type index = find_the_key_index(k);
        bucket_type& bucket = m_table[index];
        if (bucket.empty()) {
                return false;
        }
        auto curr = bucket.begin();
        auto prev = bucket.before_begin();
        while (curr != std::end(bucket)) {
                if (curr->first == k) {
                        bucket.erase_after(prev);
                        --m_size;
                        return true;
                }
                ++prev;
                ++curr;
        }
        return false;
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
bool 
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
find(const Key& k) const
{
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        const size_type index = find_the_key_index(k);
        const bucket_type& bucket = m_table[index];
        return find_key_in_bucket(k, bucket) != std::end(bucket); 
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
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        const size_type index = find_the_key_index(k);
        bucket_type& bucket = m_table[index];
        auto it = find_key_in_bucket(k, bucket);
        Value value = Value();
        if (it != std::end(bucket)) { 
                value = it->second;
        }
        return value;
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
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        if (m_table.empty()) {
                return 1.0;
        }
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
find_the_key_index(const Key& k) const
{
        return Hash()(k) % get_table_size();         
}

template<
        typename Key,
        typename Value,
        typename Hash,
        typename KeyEqual
>
decltype(auto)
separate_chaining_hash_table<Key, Value, Hash, KeyEqual>::
find_key_in_bucket(const Key& k, const bucket_type& b) const
{
        return std::find_if(std::begin(b), std::end(b), 
                                        [&](const value_type& v) 
                                        {
                                                return v.first == k; 
                                        }); 
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
                        const size_type hash  = Hash()(elem.first);
                        const size_type index = hash % nst;
                        new_table[index].push_front(std::move(elem));
                }
        }
        m_table.swap(new_table);
}

} // namespace hash_table

#endif // SEPARATE_CHAINING_HASH_TABLE_HPP
