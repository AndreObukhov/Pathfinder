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

Point::Point(short new_x, short new_y) {
    x = new_y;
    y = new_x;
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


mapElement::mapElement() : status('.'), visited(false) {}

mapElement::mapElement(const char& s) : status(s), visited(false) {}

bool mapElement::isVisited() const {
    return visited;
}

bool mapElement::isFree() const {
    // Status can be 's' for start, 'f' for finish, '.' for free cell and '#' for barrier.
    // All except for '#' are interpreted as free point:
    return status != '#';
}

void mapElement::setPrevPoint(const Point &p) {
    prevPoint = p;
}

Point mapElement::getPrevPoint() const {
    return prevPoint;
}

void mapElement::setVisited() {
    visited = true;
}

void mapElement::setStatus(const char &s) {
    status = s;
}

char mapElement::getStatus() const {
    return status;
}


map::map(const std::string& filename) {
    std::ifstream input;
    input.open(filename);

    input >> mapSize_;
    map_.resize(mapSize_, std::vector<mapElement>(mapSize_));

    char inputSymbol;
    for (short i = 0; i < mapSize_; i ++) {
        for (short j = 0; j < mapSize_; j ++) {
            input >> inputSymbol;
            if (inputSymbol == 'S')
                start_ = Point(i, j);

            if (inputSymbol == 'F')
                finish_ = Point(i, j);

            // because mapElems are '.' by default
            if (inputSymbol != '.')
                map_[i][j].setStatus(inputSymbol);
        }
    }

    input.close();
}

void map::printSizes() const {
    for (const auto& v : map_) {
        std::cout << v.size() << std::endl;
    }
}

void map::printMap() const {
    for (const auto& v: map_ ) {
        for (const auto& el: v) {
            std::cout << el.getStatus() << ' ';
        }
        std::cout << std::endl;
    }
}

char map::pointStatus(const Point& pt) const {
    if (pt.x < mapSize_ && pt.y < mapSize_) {
        return map_[pt.x][pt.y].getStatus();
    } else {
        return CELL_ACCESS_ERROR;
    }
}

bool map::isFree(const Point &pt) const {
    // to avoid accessing unassigned memory
    if (pt.x < mapSize_ && pt.y < mapSize_)
        return map_[pt.x][pt.y].isFree();
    else
        return false;
}

Point map::getStartPoint() const {
    return start_;
}

Point map::getFinishPoint() const {
    return finish_;
}
