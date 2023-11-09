cmake_minimum_required(VERSION 3.10)
project(Step1)
aux_source_directory(. SRC_LIST)
add_executable(main ${SRC_LIST})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
