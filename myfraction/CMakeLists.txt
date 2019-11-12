cmake_minimum_required(VERSION 3.14)
project(Fraction)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-g -Wall")

include_directories(.)

add_executable(runtest
        Fraction.cpp
        Fraction.h
        runtest.cpp)
