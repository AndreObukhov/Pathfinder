
#ifndef PATHFINDER_FAST_BFS_H
#define PATHFINDER_FAST_BFS_H

#include <fstream>
#include <vector>
#include <deque>
#include <tuple>
#include <iostream>
#include "map.h"

class SimpleMap{
public:
    explicit SimpleMap(const std::string& filename);
    ~SimpleMap();
    void print_start_end() const;
    std::vector<Point> bfs();
    int path_len();
    void print_steps();

protected:
    int ** field;
    int map_size;
    std::vector<Point> deltas {Point(0,-1),
                               Point(0,1),
                               Point(-1,0),
                               Point(1,0)};
    struct Point startPoint, finishPoint;
    std::deque<Point> queue;
    std::vector<Point> steps;

private:
    std::vector<Point> build_path();
};

#endif //PATHFINDER_FAST_BFS_H
