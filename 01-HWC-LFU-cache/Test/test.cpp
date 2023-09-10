#ifndef TEST_CPP
#define TEST_CPP

#include <iostream>
#include <fstream>
#include <cassert>
#include "../Include/perfect-cache.hpp"
#include "../Include/LFU-cache.hpp"

int main()
{
    std::ifstream test_data("test_data.txt");
    assert(test_data.good());

    size_t test_number = 0;
    size_t correct_tests = 0;
    size_t cache_size = 0;

    while (test_data >> cache_size)
    {
        Cache_t<int> cache(cache_size);

        std::cout << "\n" << ">>> TEST #" << ++test_number << "\n\n";

        size_t n_keys;
        test_data >> n_keys;

        int key;
        size_t hits = 0;

        while (n_keys--)
        {
            test_data >> key;
            if (cache.update(key)) ++hits;
            // cache.dump();
        }

        size_t result;
        test_data >> result;

        if (hits == result)
        {
            std::cout << ">>> SUCCESS\n";
            ++correct_tests;
        }
        else
            std::cout << ">>> ERROR: expected " << result << ", recieved" << hits << "\n";
    }

    std::cout << "\n========================================================= \n\n"
            << ">>> CORRECT TESTS: " << correct_tests << " / " << test_number << "\n\n";

    return 0;
}

#endif
