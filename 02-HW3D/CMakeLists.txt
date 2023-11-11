cmake_minimum_required(VERSION 3.12)
project(02-HW3D)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(include_list
    ./Include/Geometry2D.hpp
    ./Include/Geometry3D.hpp)

set(source_list
    ./Source/Geometry2D.cpp
    ./Source/Geometry3D.cpp )

set(main_source_list
    ./Source/triangles.cpp
    ${include_list}
    ${source_list}          )

# set(MYCOMPILE_FLAGS "-std=c++20")

add_executable(main ${main_source_list})

enable_testing()

add_subdirectory(googletest)

include_directories(./googletest/include)

add_executable(test_2D ../Test/test_2D.cpp ${source_list} ${include_list})
add_executable(test_3D ../Test/test_3D.cpp ${source_list} ${include_list})
# add_executable(test_main ./Test/test_main.cpp ${include_list})

target_link_libraries(test_2D gtest)
target_link_libraries(test_3D gtest)
# target_link_libraries(test_main PRIVATE gtest)

# include(GoogleTest)
# gtest_discover_tests(test2D)
# gtest_discover_tests(test3D)
# gtest_discover_tests(test_main)
