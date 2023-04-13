cmake_minimum_required(VERSION 3.17)
project(graph_project)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        AdjListDirNetwork.h.h
        AdjListDirNetworkArc.h
        AdjListDirNetworkVex.h
        Assistance.h
        LinkStack.h
        Node.h
        ShortestPathFloyd.h
        TestShortestPathFloyd.cpp
        )


add_executable(graph_project TestShortestPathFloyd.cpp ${SOURCE_FILES} ${SOURCES})

