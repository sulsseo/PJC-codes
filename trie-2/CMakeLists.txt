cmake_minimum_required(VERSION 3.8)
project(trie-2)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(trie-2 ${SOURCE_FILES})

project(tests)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        catch.hpp
        tests-main.cpp
        trie-tests.cpp
        trie.hpp
        trie.cpp
        trie-1.hpp
        trie-1.cpp)
add_executable(tests ${SOURCE_FILES})