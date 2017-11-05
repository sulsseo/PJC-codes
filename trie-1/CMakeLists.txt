cmake_minimum_required(VERSION 3.8)
project(tests)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES
        catch.hpp
        tests-helpers.hpp
        tests-main.cpp
        trie-tests.cpp
        trie.cpp
        trie.hpp)
add_executable(tests ${SOURCE_FILES})

project(trie)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES
        main.cpp
        )
add_executable(trie ${SOURCE_FILES})