cmake_minimum_required(VERSION 3.17)
project(PathFinder)

set(CMAKE_CXX_STANDARD 17)

add_executable(PathFinder main.cpp
        profile.h
        map.cpp map.h
        finder_bfs.cpp finder_bfs.h
        map_generator.cpp map_generator.h
        finder_a_star.cpp finder_a_star.h
        fast_bfs.cpp fast_bfs.h)