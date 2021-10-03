#include <iostream>

#include "map.h"
#include "finder_bfs.h"

int main() {
    map m("../map.txt");
    m.printMap();
    std::cout << "--------------------" << std::endl;

    std::deque<Point> route = findRoute(m);
    m.markRoute(route);
    m.printMap();
    return 0;
}
