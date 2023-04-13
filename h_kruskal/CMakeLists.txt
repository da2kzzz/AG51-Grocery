cmake_minimum_required(VERSION 3.17)
project(h_kruskal)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        assistance.h
        heads.h
        )


add_executable(h_kruskal main.cpp ${SOURCE_FILES} ${SOURCES})