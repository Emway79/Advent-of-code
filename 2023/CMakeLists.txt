cmake_minimum_required(VERSION 3.24)
project(AdventOfCode2023)

set(CMAKE_CXX_STANDARD 23)

include_directories("C:/Curl")

add_executable(AdventOfCode2023
        #MAIN
        main.cpp

        #LIBS
        Libraries/utils.hpp
        Libraries/utils.tpp
        Libraries/utils.cpp

        #DAYS
        Days/Days2023.hpp

        Days/Day1.cpp
        Days/Day2.cpp
        )
