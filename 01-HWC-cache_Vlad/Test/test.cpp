#include <iostream>
#include <string>
#include <vector>
#include <new>
#include <climits>
#include "../Include/cache.hpp"

int main()
{
    int size;
    std::cin >> size;
    Cache_t<int> cache(size);

    int n_pages;
    std::cin >> n_pages;

    for (int i = 0; i < n_pages; i++)
    {
        int new_page_key;
        std::cin >> new_page_key;
        cache.update(new_page_key);
    }

    // cache.dump();

    return 0;
}
