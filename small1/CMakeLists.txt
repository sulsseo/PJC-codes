cmake_minimum_required(VERSION 3.7)
project(hw01)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        small1.hpp
        small1.cpp
        tests-small1.cpp
        tests-main.cpp
        catch.hpp)

add_executable(hw01 ${SOURCE_FILES})

project(tests)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        small1.hpp
        small1.cpp
        tests-small1.cpp
        tests-main.cpp
        catch.hpp)

add_executable(tests ${SOURCE_FILES})

project(main)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp)

add_executable(main ${SOURCE_FILES})