#include <iostream>

#include "map.h"
#include "finder_bfs.h"
#include "profile.h"

#include "map_generator.h"

int main() {

    /*
    bfsInts::map m("../gen.txt");
    for (int i = 0; i < 20; i ++) {
        std::cout << m.getDist(Point(i, 0)) << " ";
    }
    std::cout << std::endl;
    m.printMap();
    */

    generateMap(200, 20, "../gen.txt");

    bfsPoints::map m_pts("../gen.txt");
    //m.printMap();
    //std::cout << "--------------------" << std::endl;
    std::deque<Point> route;
    {
        LOG_DURATION("BFS algorithm with Points");
        route = bfsPoints::findRoute(m_pts);
    }
    if (!route.empty()) {
        m_pts.markRoute(route);
        // m_pts.printMap();
    }

    bfsInts::map m_ints("../gen.txt");
    {
        LOG_DURATION("BFS algorithm with Ints");
        route = bfsInts::findRoute(m_ints);
    }

    if (!route.empty()) {
        m_ints.markRoute(route);
        // m_ints.printMap();
    }
    else {
        if (m_ints.getStartPoint() == m_ints.getFinishPoint()) {
            std::cout << "Start and end points are the same." << std::endl;
        }
        else {
            std::cout << "No route" << std::endl;
        }
    }

    return 0;
}
