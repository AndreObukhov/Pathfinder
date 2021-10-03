#include <iostream>

#include "map.h"

int main() {
    map m("../map.txt");
    m.printMap();

    Point pt = {0, 0};
    // std::cout << pt << std::endl;
    std::cout << m.pointStatus(pt) << std::endl;
    std::cout << m.isFree(pt) << std::endl;
    pt.x = 11;
    std::cout << m.pointStatus(pt) << std::endl;

    Point a(3 ,2);
    Point b(1, 2);
    std::cout << a - b << std::endl;

    return 0;
}
