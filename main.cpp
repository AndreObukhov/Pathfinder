#include <iostream>

#include "map.h"
#include "finder_bfs.h"
#include "finder_a_star.h"
#include "profile.h"

#include "map_generator.h"
#include "fast_bfs.h"


int main() {
    generateMap(5000, 20, "../gen.txt");

    std::cout << "--------------------" << std::endl;

    std::string filename = "../gen.txt";

    bfsPoints::map map_bfs_p(filename);
    std::deque<Point> route;
    {
        LOG_DURATION("BFS algorithm with Points");
        route = bfsPoints::findRoute(map_bfs_p);
    }
    if (!route.empty()) {
        std::cout << route.size() << std::endl;
    }

    bfsInts::map map_bfs_i(filename);
    {
        LOG_DURATION("BFS algorithm with Ints");
        route = bfsInts::findRoute(map_bfs_i);
    }
    if (!route.empty()) {
        std::cout << route.size() << std::endl;
    }

    SimpleMap map_s(filename);
    {
        LOG_DURATION("BFS on simple map")
        auto steps = map_s.bfs();
    }

    astarPoints::map map_a(filename);
    {
        LOG_DURATION("A-Star algorithm with Points");
        route = astarPoints::findRoute(map_a);
    }
    if (!route.empty()) {
        std::cout << route.size() << std::endl;
    }


    if (!route.empty()) {
        map_bfs_p.markRoute(route);
        //m.printMap();
    }
    else {
        if (map_bfs_p.getStartPoint() == map_bfs_p.getFinishPoint()) {
            std::cout << "Start and end points are the same." << std::endl;
        }
        else {
            std::cout << "No route" << std::endl;
        }
    }

    return 0;
}
