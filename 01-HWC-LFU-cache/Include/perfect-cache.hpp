#ifndef PERFECT_CACHE_HPP
#define PERFECT_CACHE_HPP

#include <iostream>
#include <unordered_map>
#include <iterator>
#include <list>

template <typename T, typename KeyT = int>
struct Perfect_cache_t
{
    using ListT  = typename std::list<std::pair<KeyT, std::pair<T, size_t>>>;
    using ListIt = typename ListT::iterator;
    using HashT  = typename std::unordered_map<KeyT, ListIt>;
    using HashIt = typename HashT::iterator;

    size_t  size_   ;
    ListT   cache_  ;
    HashT   hash_t_ ;

    Perfect_cache_t(size_t size) { size_ = size; }

    bool is_full() const { return (cache_.size() == size_); }

    void dump()
    {
        std::cout << "Cache_t dump: \n{\n\tkey :";
        for (ListIt it = cache_.begin(); it != cache_.end(); ++it) { fprintf(stdout, "%3d", it->first); }
        std::cout << "\n\tfreq:";
        for (ListIt it = cache_.begin(); it != cache_.end(); ++it) { fprintf(stdout, "%3ld", it->second.second); }
        std::cout << "\n}\n\n";
    }

    bool update(KeyT key)
    {
        if (size_ == 0) return false;

        auto hit = hash_t_.find(key);

        if (hit != hash_t_.end())
        {
            hit->second->second.second++;

            if ((hit->second != cache_.begin()) &&
                (hit->second->second.second > std::prev(hit->second)->second.second))
            {
                cache_.splice(std::prev(hit->second), cache_, hit->second);
            }

            // dump();
            return true;
        }

        std::pair<KeyT, std::pair<T, size_t>> new_page;
        new_page.second.second = 1;
        new_page.first = key;

        if (is_full())
        {
            hash_t_.erase(cache_.back().first);
            cache_.pop_back();
        }

        cache_.push_back(new_page);
        hash_t_.emplace(key, std::prev(cache_.end()));

        // dump();
        return false;
    }
};

#endif
