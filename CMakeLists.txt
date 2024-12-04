cmake_minimum_required(VERSION 3.24)
project(AOC2023)

set(CMAKE_CXX_STANDARD 20)

add_executable(AOC2023
        #MAIN
        src/main.cpp

        #LIBS
        src/Libraries/utils.hpp
        src/Libraries/utils.tpp
        src/Libraries/utils.cpp

        #DAYS
        src/Days/Day.hpp

        src/Days/Day1.cpp
        src/Days/Day2.cpp
        src/Days/Day3.cpp
        src/Days/Day4.cpp
        src/Days/Day5.cpp
        src/Days/Day6.cpp
        src/Days/Day7.cpp
        src/Days/Day8.cpp
        src/Days/Day9.cpp
        src/Days/Day10.cpp
        src/Days/Day11.cpp
        src/Days/Day12.cpp
        src/Days/Day13.cpp
        src/Days/Day14.cpp
        src/Days/Day15.cpp
        src/Days/Day16.cpp
        src/Days/Day17.cpp
        src/Days/Day18.cpp
        src/Days/Day19.cpp
        src/Days/Day20.cpp
        src/Days/Day21.cpp
        src/Days/Day22.cpp
)
