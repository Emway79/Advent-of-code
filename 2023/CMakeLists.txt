cmake_minimum_required(VERSION 3.24)
project(AdventOfCode2023)

set(CMAKE_CXX_STANDARD 23)

add_executable(AdventOfCode2023
        #MAIN
        main.cpp

        #LIBS
        Libraries/utils.hpp
        Libraries/utils.tpp
        Libraries/utils.cpp

        #DAYS
        Days/Day.hpp

        Days/Day1.cpp
        Days/Day2.cpp
        Days/Day3.cpp
        Days/Day4.cpp
        Days/Day5.cpp
        Days/Day6.cpp
        Days/Day7.cpp
        Days/Day8.cpp
        Days/Day9.cpp
        Days/Day10.cpp
        Days/Day11.cpp
        Days/Day12.cpp
        Days/Day13.cpp
        Days/Day13.cpp
        Days/Day13.cpp
        Days/Day14.cpp
        Days/Day15.cpp
        Days/Day16.cpp
        Days/Day17.cpp
        Days/Day18.cpp
        Days/Day19.cpp
)
