cmake_minimum_required(VERSION 3.17)
project(pj_tu)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        heads.h
        assistance.h
        main.cpp
        )


add_executable(pj_tu main.cpp ${SOURCE_FILES} ${SOURCES})