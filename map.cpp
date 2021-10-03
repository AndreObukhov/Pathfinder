//
// Created by Andrew on 9/22/21.
//

#include "map.h"
#include <iostream>
#include <fstream>


Point::Point() {
    col = 0;
    row = 0;
}

Point::Point(short new_col, short new_row) {
    col = new_col;
    row = new_row;
}


bool operator == (const Point& p1, const Point& p2) {
    return (p1.col == p2.col && p1.row == p2.row);
}

Point operator - (const Point& p1, const Point& p2) {
    return Point(p1.col - p2.col, p1.row - p2.row);
}

Point operator + (const Point& p1, const Point& p2) {
    return Point(p1.col + p2.col, p1.row + p2.row);
}

std::ostream& operator << (std::ostream& o, const Point& p) {
    o << "(" << p.col << ":" << p.row << ")";
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

bool mapElement::needToVisit() const {
    return (this->isFree() && !this->isVisited());
}


map::map(const std::string& filename) {
    std::ifstream input;
    input.open(filename);

    input >> mapSize_;
    map_.resize(mapSize_, std::vector<mapElement>(mapSize_));

    char inputSymbol;
    for (short row = 0; row < mapSize_; row ++) {
        for (short col = 0; col < mapSize_; col ++) {
            input >> inputSymbol;
            if (inputSymbol == 'S')
                start_ = Point(col, row);

            if (inputSymbol == 'F')
                finish_ = Point(col, row);

            // because mapElems are '.' by default
            if (inputSymbol != '.')
                map_[row][col].setStatus(inputSymbol);
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

short map::getSize() const {
    return mapSize_;
}

char map::pointStatus(const Point& pt) const {
    if (pt.col < mapSize_ && pt.row < mapSize_) {
        return map_[pt.row][pt.col].getStatus();
    } else {
        return CELL_ACCESS_ERROR;
    }
}

bool map::isFree(const Point &pt) const {
    // to avoid accessing unassigned memory
    if (pt.col < mapSize_ && pt.row < mapSize_)
        return map_[pt.row][pt.col].isFree();
    else
        return false;
}

bool map::isVisited(const Point &pt) const {
    return map_[pt.row][pt.col].isVisited();
}

void map::setVisited(const Point &pt) {
    map_[pt.row][pt.col].setVisited();
}

bool map::needToVisit(const Point &pt) const {
    return map_[pt.row][pt.col].needToVisit();
}

void map::setPrevPoint(const Point &current, const Point &prev) {
    map_[current.row][current.col].setPrevPoint(prev);
}

Point map::getPrevPoint(const Point &pt) const {
    return map_[pt.row][pt.col].getPrevPoint();
}

Point map::getStartPoint() const {
    return start_;
}

Point map::getFinishPoint() const {
    return finish_;
}

void map::markRoute(const std::deque<Point> &route) {
    for (const Point& pt : route) {
        if (!(pt == finish_) && !(pt == start_)) {
            map_[pt.row][pt.col].setStatus('*');
        }
    }
}
