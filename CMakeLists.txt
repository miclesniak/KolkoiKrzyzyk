cmake_minimum_required(VERSION 3.21)
project(Kolko_i_krzyzyk)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Kolko_i_krzyzyk
        kolko_i_krzyzyk.cpp
        kolko_i_krzyzyk.hh
        main.cpp)
