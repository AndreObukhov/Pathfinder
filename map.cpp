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

bool operator != (const Point& p1, const Point& p2) {
    return (p1.col != p2.col || p1.row != p2.row);
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



mapElem::mapElem() {
    status = '.';
    visited = false;
}
mapElem::mapElem(const char& s) {
    status = s;
    visited = false;
}

void mapElem::setStatus(const char &s) {
    status = s;
}

char mapElem::getStatus() const {
    return status;
}

bool mapElem::isFree() const {
    return status != '#';
}

bool mapElem::isVisited() const {
    return visited;
}
void mapElem::setVisited() {
    visited = true;
}
bool mapElem::needToVisit() const {
    return (this->isFree() && !this->isVisited());
}

void bfsPoints::mapElement::setPrevPoint(const Point &p) {
    prevPoint = p;
}

Point bfsPoints::mapElement::getPrevPoint() const {
    return prevPoint;
}

bfsPoints::map::map(const std::string& filename) {
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

bfsPoints::map::map(const short& size, const int& barrierPercent) {
    mapSize_ = size;

    std::random_device rd;          // only used once to initialise (seed) engine
    std::mt19937 rng(rd());         // random-number engine used (Mersenne-Twister)
    std::uniform_int_distribution<int> uni(0, 100);     // guaranteed unbiased

    map_.resize(size);
    for (int i = 0; i < size; i ++) {
        std::vector<mapElement> line(size);
        for (int j = 0; j < size; j++) {
            int a = uni(rng);
            if (a % 100 < barrierPercent) {
                line[j].setStatus('#');
            } else {
                line[j].setStatus('.');
            }
        }
        map_[i] = line;
    }
}

void bfsPoints::map::printMap() const {
    for (const auto& v: map_ ) {
        for (const auto& el: v) {
            std::cout << el.getStatus() << ' ';
        }
        std::cout << std::endl;
    }
}

short bfsPoints::map::getSize() const {
    return mapSize_;
}

char bfsPoints::map::pointStatus(const Point& pt) const {
    if (pt.col < mapSize_ && pt.row < mapSize_) {
        return map_[pt.row][pt.col].getStatus();
    } else {
        return CELL_ACCESS_ERROR;
    }
}

bool bfsPoints::map::isFree(const Point &pt) const {
    // to avoid accessing unassigned memory
    if (pt.col < mapSize_ && pt.row < mapSize_)
        return map_[pt.row][pt.col].isFree();
    else
        return false;
}

bool bfsPoints::map::isVisited(const Point &pt) const {
    return map_[pt.row][pt.col].isVisited();
}

void bfsPoints::map::setVisited(const Point &pt) {
    map_[pt.row][pt.col].setVisited();
}

bool bfsPoints::map::needToVisit(const Point &pt) const {
    return map_[pt.row][pt.col].needToVisit();
}

void bfsPoints::map::setPrevPoint(const Point &current, const Point &prev) {
    map_[current.row][current.col].setPrevPoint(prev);
}

Point bfsPoints::map::getPrevPoint(const Point &pt) const {
    return map_[pt.row][pt.col].getPrevPoint();
}

Point bfsPoints::map::getStartPoint() const {
    return start_;
}

Point bfsPoints::map::getFinishPoint() const {
    return finish_;
}

void bfsPoints::map::markRoute(const std::deque<Point> &route) {
    for (const Point& pt : route) {
        if (pt != finish_ && pt != start_) {
            map_[pt.row][pt.col].setStatus('*');
        }
    }
}
