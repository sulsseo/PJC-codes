cmake_minimum_required(VERSION 3.8)
project(main)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES
        main.cpp
        expr.cpp
        )
add_executable(main ${SOURCE_FILES})

project(tests)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES
        catch.hpp
        expr.cpp
        tests-main.cpp
        tests-small6-data.cpp
        tests-small6.cpp
        )
add_executable(tests ${SOURCE_FILES})