
#ifndef PATHFINDER_FAST_BFS_H
#define PATHFINDER_FAST_BFS_H

#include <fstream>
#include <vector>
#include <deque>
#include <tuple>
#include <iostream>

class SimpleMap{
public:
    explicit SimpleMap(const std::string& filename);
    void print_start_end() const;
    std::vector<std::tuple<int, int>> bfs();
    int path_len();
    void print_steps();

protected:
    int ** field;
    int map_size;
    std::vector<std::tuple<int, int>> deltas {std::make_tuple(0,-1),
                                              std::make_tuple(0,1),
                                              std::make_tuple(-1,0),
                                              std::make_tuple(1,0)};
    int start_x, start_y, finish_x, finish_y;
    std::deque<std::tuple<int,int>> queue;
    std::vector<std::tuple<int,int>> steps;

private:
    std::vector<std::tuple<int, int>> build_path();
};

#endif //PATHFINDER_FAST_BFS_H
