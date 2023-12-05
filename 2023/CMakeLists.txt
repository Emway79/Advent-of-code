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
        Days/Day5.cpp)
