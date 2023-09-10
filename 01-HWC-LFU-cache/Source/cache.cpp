#ifndef CACHE_CPP
#define CACHE_CPP

#include <iostream>
#include "../Include/perfect-cache.hpp"
#include "../Include/LFU-cache.hpp"

int main()
{
    size_t correct_tests = 0;
    size_t cache_size    = 0;

    std::cin >> cache_size;
    Cache_t<int> cache(cache_size);

    size_t n_page;
    std::cin >> n_page;

    int key     = 0;
    size_t hits = 0;

    std::vector<int> page_keys(n_page);

    for (int i = 0; i < n_page; i++)
    {
        std::cin >> key;
        page_keys[i] = key;

        if (cache.update(key)) ++hits;
        // cache.dump();
    }

    std::cout << "LFU     cache: " << hits << "\n";
    std::cout << "perfect cache: " << perfect_cache_hits(cache_size, n_page, page_keys) << "\n";

    return 0;
}

#endif
