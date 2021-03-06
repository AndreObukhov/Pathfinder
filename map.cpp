//
// Created by Andrew on 9/22/21.
//

#include "map.h"

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

// -------------------------------------------------------------------

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

// -------------------------------------------------------------------

void bfsPoints::mapElement::setPrevPoint(const Point &p) {
    prevPoint = p;
}

Point bfsPoints::mapElement::getPrevPoint() const {
    return prevPoint;
}

// -------------------------------------------------------------------

// initializing parent class
bfsPoints::map::map(const std::string& filename) : mapT<bfsPoints::mapElement>(filename) {}

void bfsPoints::map::setPrevPoint(const Point &current, const Point &prev) {
    map_[current.row][current.col].setPrevPoint(prev);
}

Point bfsPoints::map::getPrevPoint(const Point &pt) const {
    return map_[pt.row][pt.col].getPrevPoint();
}

// -------------------------------------------------------------------

void astarPoints::mapElement::setCost(const int& newCost)  {
    cost = newCost;
}

int astarPoints::mapElement::getCost() const  {
    return cost;
}
void astarPoints::mapElement::setPrevPoint(const Point &prev) {
    prevPoint = prev;
}

Point astarPoints::mapElement::getPrevPoint() const {
    return prevPoint;
}

// -------------------------------------------------------------------

astarPoints::map::map(const std::string& filename) : mapT<astarPoints::mapElement>(filename) {}

void astarPoints::map::setCost(const Point &current, const int &newCost) {
    map_[current.row][current.col].setCost(newCost);
}

int astarPoints::map::getCost(const Point &current) const {
    return map_[current.row][current.col].getCost();
}

void astarPoints::map::setPrevPoint(const Point &current, const Point &prev) {
    map_[current.row][current.col].setPrevPoint(prev);
}

Point astarPoints::map::getPrevPoint(const Point &pt) const {
    return map_[pt.row][pt.col].getPrevPoint();
}

// ----------------------------------------------------------

bfsInts::mapElement::mapElement() {
    status = '.';
    visited = false;
    dist = INT_MAX;
}

void bfsInts::mapElement::setDist(const int &d) {
    dist = d;
}

int bfsInts::mapElement::getDist() const {
    return dist;
}

void bfsInts::map::setDist(const Point &current, const int &d) {
    map_[current.row][current.col].setDist(d);
}

int bfsInts::map::getDist(const Point &pt) const {
    return map_[pt.row][pt.col].getDist();
}

bfsInts::map::map(const std::string& filename) : mapT<bfsInts::mapElement>(filename) {}
