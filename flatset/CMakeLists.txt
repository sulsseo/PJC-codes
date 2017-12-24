cmake_minimum_required(VERSION 3.8)
project(flatset)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES
        main.cpp
        lazyflat.h
        )
add_executable(flatset ${SOURCE_FILES})

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