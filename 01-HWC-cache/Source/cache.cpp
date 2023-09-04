#include <iostream>
#include <unordered_map>
#include "../Include/cache.hpp"

template<typename T, typename KeyT = int>
struct cache_t
{
    using ListT = typename std::list<std::pair<T, size_t>>;
    using ListIt = typename listT::iterator;

    cache_t(size_t size) : size_(size) {}

    bool full() const { return (size_ == 0); }

    template<typename FunT>
    bool lookup_update(KeyT key, FunT get_page)
    {
        auto hit = hash_.find(key);

        if (hit == hash_.end())
        {
            if (full())
            {
                ...
            }
            ...
        }
        ...
    }

    ListT cache_;
    std::unordered_map<KeyT, ListIt> hash_;
    size_t size_;
};
