cmake_minimum_required(VERSION 3.8)
project(trie-3)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES
        main.cpp
        )
add_executable(trie-3 ${SOURCE_FILES})

project(tests)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES
        flatset.h
        catch.hpp
        tests-main.cpp
        tests-helpers.hpp
        tests-helpers.cpp
        test_flatset.cpp
        )
add_executable(tests ${SOURCE_FILES})