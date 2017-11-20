cmake_minimum_required(VERSION 3.8)
project(trie-3)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES
        main.cpp
        trie.cpp
        )
add_executable(trie-3 ${SOURCE_FILES})

project(tests)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES
        catch.hpp
        tests-main.cpp
        trie-tests.cpp
        trie.hpp
        trie.cpp
        )
add_executable(tests ${SOURCE_FILES})