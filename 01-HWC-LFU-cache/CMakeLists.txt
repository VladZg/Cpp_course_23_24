cmake_minimum_required(VERSION 3.10)
project(01-HWC-LFU-cache)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(include_list
    ./Include/perfect-cache.hpp
    ./Include/LFU-cache.hpp     )

set(main_source_list
    ./Source/cache.cpp
    ${include_list}     )

set(test_source_list
    ./Test/test.cpp
    ./Test/test_data.txt
    ${include_list}     )

add_executable(cache ${main_source_list})
add_executable(test  ${test_source_list})
