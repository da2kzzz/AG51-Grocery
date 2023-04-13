cmake_minimum_required(VERSION 3.9)
project(Cars)

link_directories("C:/Program Files/MinGW/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D FREEGLUT_STATIC")

add_executable(Cars main.cpp Cars.cpp Cars.h determinant.cpp determinant.h Icon.h Mesh.cpp Mesh.h Polygon.cpp Polygon.h Triangle.h Vector2D.cpp Vector2D.h Voronoi.cpp Voronoi.h glutWindows.cpp glutWindows.h)
target_link_libraries(Cars freeglut_static opengl32 winmm gdi32 glu32.lib)