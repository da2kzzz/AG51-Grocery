cmake_minimum_required(VERSION 3.17)
project(vorTest)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        Delaunay.h					//*号对应具体的文件名
        Delaunay.cpp
        GeometryUtil.cpp
        GeometryUtil.h
        Vec3.cpp
        Vec3.h
        Voronoi.cpp
        Voronoi.h
        )


add_executable(vorTest main.cpp ${SOURCE_FILES} ${SOURCES})