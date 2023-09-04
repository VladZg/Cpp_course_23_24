#ifndef CACHE_HPP
#define CACHE_HPP

#include <iostream>
#include <unordered_map>
#include <iterator>
#include <list>

template<typename T, typename KeyT = int>
struct cache_t
{
    using ListT =   typename std::list<std::pair<T, size_t>>;
    using ListIt =  typename ListT::iterator;
    using HashT =   typename std::unordered_map<KeyT, ListIt>;

    cache_t(size_t size)
    {
        size_ = size;

        for (ListIt it = cache_.begin(); it != cache_.end(); ++it) { it->second = 0; }
    }

    bool full() const { return (size_ == 0); }

    template<typename FunT>
    bool lookup_update(KeyT key, FunT get_page)
    {
        auto hit = hash_.find(key);

        if (hit == hash_.end())
        {
            if (full())
            {
                return false;
            }
        }
        return true;
    }

    ListT cache_;
    HashT hash_;
    size_t size_;
};

#endif