cmake_minimum_required(VERSION 3.8)
project(semestral)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(SOURCE_FILES
        main.cpp
        graph.cpp
        printer.hpp
        )
add_executable(semestral ${SOURCE_FILES})

project(tester)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(SOURCE_FILES
        test.cpp
        )
add_executable(tester ${SOURCE_FILES})