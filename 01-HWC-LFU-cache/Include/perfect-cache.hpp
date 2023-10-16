#ifndef PERFECT_CACHE_HPP
#define PERFECT_CACHE_HPP

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <list>
#include <vector>

int perfect_cache_hits(size_t cache_size, int n_page, std::vector<int> page_keys)
{
    int hits = 0;

    using VectIt = typename std::vector<int>::iterator;
    std::unordered_map<int, VectIt> next_appearance;

    for (int i = n_page - 1; i >= 0; i--)
        next_appearance[page_keys[i]] = std::find(page_keys.begin() + i + 1, page_keys.end(), page_keys[i]);

    std::list<int> cache;

    for (int i = 0; i < n_page; i++)
    {
        int cur = page_keys[i];

        // in case it's a hit
        if (std::find(cache.begin(), cache.end(), cur) != cache.end())
        {
            hits++;
            continue;
        }

        next_appearance[cur] = std::find(page_keys.begin() + i + 1, page_keys.end(), cur);
        if (next_appearance[cur] == page_keys.end()) continue;

        // in case it isn't a hit and list isn't full
        if (cache.size() < cache_size)
        {
            cache.push_back(cur);
            continue;
        }

        // in case cache is full and the page is new
        int max_dist = 0;
        int value_to_delete = -1;

        for (std::list<int>::iterator it = cache.begin(), c_end = cache.end(); it != c_end; ++it)
        {
            VectIt next = next_appearance[*it];

            // delete page that doesn't occur later
            if (next == page_keys.end())
            {
                value_to_delete = *it;
                break;
            }

            // look for the element that occurs the latest
            if ((next - page_keys.begin()) > max_dist)
            {
                max_dist = next - page_keys.begin();
                value_to_delete = *it;
            }
        }

        cache.remove(value_to_delete);
        cache.push_back(cur);
    }

    return hits;
}

#endif
