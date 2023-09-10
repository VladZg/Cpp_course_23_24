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

    size_t n_keys;
    std::cin >> n_keys;

    int key     = 0;
    size_t hits = 0;

    while (n_keys--)
    {
        std::cin >> key;
        if (cache.update(key)) ++hits;
        // cache.dump();
    }

    std::cout << hits << "\n";

    return 0;
}

#endif
