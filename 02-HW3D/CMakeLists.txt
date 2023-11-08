cmake_minimum_required(VERSION 3.10)
project(01-HWC-LFU-cache)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(include_list
    ./Include/Geometry2D.hpp
    ./Include/Geometry3D.hpp)

set(main_source_list
    ./Source/triangles.cpp
    ${include_list}         )

set(test_source_list
    ./Test/test.cpp
    ${include_list}     )

add_executable(main ${main_source_list})
add_executable(test ${test_source_list})
