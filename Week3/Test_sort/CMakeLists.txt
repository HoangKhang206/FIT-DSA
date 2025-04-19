cmake_minimum_required(VERSION 3.29)
project(Test_sort)

set(CMAKE_CXX_STANDARD 20)

add_executable(Test_sort main.cpp
        Sort.h
        Sort_function.cpp)
