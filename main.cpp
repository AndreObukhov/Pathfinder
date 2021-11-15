#include <iostream>

#include "map.h"
#include "finder_bfs.h"
#include "finder_a_star.h"
#include "profile.h"

#include "map_generator.h"


int main() {
    // generateMap(30, 20, "../gen.txt");

    bfsPoints::map m("../map.txt");
    // m.printMap();
    std::cout << "--------------------" << std::endl;

    std::deque<Point> route;

    {
        LOG_DURATION("BFS algorithm with Points");
        route = bfsPoints::findRoute(m);
    }
    astarPoints::map a_map("../map.txt");
    {
        LOG_DURATION("A-Star algorithm with Points");
        route = astarPoints::findRoute(a_map);
    }

    if (!route.empty()) {
        m.markRoute(route);
        //m.printMap();
    }
    else {
        if (m.getStartPoint() == m.getFinishPoint()) {
            std::cout << "Start and end points are the same." << std::endl;
        }
        else {
            std::cout << "No route" << std::endl;
        }
    }

    return 0;
}
