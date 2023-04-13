cmake_minimum_required(VERSION 3.17)
project(dln_test)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        svpng.inc
        )


add_executable(dln_test main.cpp)