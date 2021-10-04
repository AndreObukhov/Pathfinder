cmake_minimum_required(VERSION 3.17)
project(PathFinder)

set(CMAKE_CXX_STANDARD 17)

add_executable(PathFinder main.cpp
        profile.h
        map.cpp map.h
        finder_bfs.cpp finder_bfs.h)