cmake_minimum_required(VERSION 3.8)
project(trie)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(trie ${SOURCE_FILES})

project(tests)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        tests-main.cpp
        tests-helpers.hpp
        trie-tests.cpp
        trie.hpp
        trie.cpp)
add_executable(tests ${SOURCE_FILES})