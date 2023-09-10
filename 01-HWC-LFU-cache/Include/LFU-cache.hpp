#ifndef LFU_CACHE_HPP
#define LFU_CACHE_HPP

#include <iostream>
#include <unordered_map>
#include <iterator>
#include <list>

template <typename T, typename KeyT = int>
struct Cache_t
{
    using ListT  = typename std::list<std::pair<KeyT, std::pair<T, size_t>>>;
    using ListIt = typename ListT::iterator;
    using HashT  = typename std::unordered_map<KeyT, ListIt>;
    using HashIt = typename HashT::iterator;

    size_t  size_   ;
    ListT   cache_  ;
    HashT   hash_t_ ;

    Cache_t(size_t size) { size_ = size; }

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

        // in case page is already in cache
        if (hit != hash_t_.end())
        {
            hit->second->second.second++;   // page_frequency++

            if ((hit->second != cache_.begin()) &&
                (hit->second->second.second > std::prev(hit->second)->second.second))   // if frequency of just added page > frequency of a previous page
            {
                cache_.splice(std::prev(hit->second), cache_, hit->second); // swap just added page and that near page
            }

            // dump();
            return true;
        }

        // in case page is not in cache
        std::pair<KeyT, std::pair<T, size_t>> new_page;
        new_page.second.second = 1;
        new_page.first = key;

        if (is_full())  // if cache is full
        {
            hash_t_.erase(cache_.back().first); // delete the last (the less frequent) page from cache
            cache_.pop_back();
        }

        cache_.push_back(new_page); // add a new page to cache
        hash_t_.emplace(key, std::prev(cache_.end()));

        // dump();
        return false;
    }
};

#endif
