#include <iostream>
#include <string>
#include <vector>
#include <new>
#include <climits>
#include <fstream>
#include <sstream>
#include "../Include/cache.hpp"

void test_file(std::string filename)
{
    std::ifstream test_data(filename);

    if (test_data.is_open())
    {
        size_t test_number = 0;
        size_t correct_tests = 0;
        size_t cache_size;

        while (test_data >> cache_size)
        {
            Cache_t<int> cache(cache_size);

            std::cout << "\n" << ">>> TEST #" << ++test_number << "\n\n";

            size_t number_of_keys;
            test_data >> number_of_keys;

            int key;
            size_t hits = 0;

            while (number_of_keys-- != 0)
            {
                test_data >> key;
                if (cache.update(key)) ++hits;
                cache.dump();
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
    }
}

int main()
{
    test_file("test_data.txt");

    return 0;
}
