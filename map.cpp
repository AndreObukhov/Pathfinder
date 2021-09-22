//
// Created by Andrew on 9/22/21.
//

#include "map.h"
#include <iostream>
#include <fstream>


Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(unsigned new_y, unsigned new_x) {
    x = new_x;
    y = new_y;
}


bool operator == (const Point& p1, const Point& p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}

Point operator - (const Point& p1, const Point& p2) {
    return Point(p1.x - p2.x, p1.y - p2.y);
}

std::ostream& operator << (std::ostream& o, const Point& p) {
    o << "(" << p.x << ":" << p.y << ")";
    return o;
}


map::map(const std::string& filename) {
    std::ifstream input;
    input.open(filename);

    input >> mapSize_;
    map_.resize(mapSize_, std::vector<char>(mapSize_));

    char inputSymbol;
    for (unsigned i = 0; i < mapSize_; i ++) {
        for (unsigned j = 0; j < mapSize_; j ++) {
            input >> inputSymbol;
            if (inputSymbol == 'S') {
                start_.x = j;
                start_.y = i;
                // map_[i][j] = '.';
            }
            if (inputSymbol == 'F') {
                finish_.x = j;
                finish_.y = i;
                // map_[i][j] = '.';
            }
            map_[i][j] = inputSymbol;
        }
    }

    input.close();
}

void map::checkSize() {
    for (const auto& v : map_) {
        std::cout << v.size() << std::endl;
    }
}

void map::printMap() {
    for (const auto& v: map_ ) {
        for (const auto& el: v) {
            std::cout << el << ' ';
        }
        std::cout << std::endl;
    }
}

char map::pointStatus(const Point& pt) {
    if (pt.x < mapSize_ && pt.y < mapSize_) {
        return map_[pt.x][pt.y];
    } else {
        return CELL_ACCESS_ERROR;
    }
}
