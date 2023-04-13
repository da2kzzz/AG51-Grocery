cmake_minimum_required(VERSION 3.17)
project(td16)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        convexhull.h
        convexhull.cpp
        Delaunay.pro
        kdtree.h
        kdtree.cpp
        sort.cpp
        sort.h
        reforence.h
        widget.cpp
        widget.h
        widget.ui
        img.qrc
        )


add_executable(Delaunay-master main.cpp ${SOURCE_FILES} ${SOURCES})