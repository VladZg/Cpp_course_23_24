#include <iostream>
#include <string>
#include <vector>
#include <new>
#include <climits>
#include "../Include/cache.hpp"

int main()
{
    int n = 3;

    // std::cin >> n;

    Cache_t<int> cache(n);

    cache.update(1);
    cache.update(2);
    cache.update(3);
    cache.update(2);
    cache.update(4);
    cache.update(2);
    cache.update(5);
    cache.update(4);
    cache.update(1);

    // cache.dump();

    return 0;
}
