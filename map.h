//
// Created by Andrew on 9/22/21.
//

#ifndef PATHFINDER_MAP_H
#define PATHFINDER_MAP_H

#include <vector>
#include <string>
#include <deque>

// special value returned if point coordinates is out of map range
#define CELL_ACCESS_ERROR 'E'

/**
 * Struct representing point of the map. Contains point's coordinates.
 */
typedef struct Point {
    /**
     * The default-est constructor possible. Initializes col and row fields with zeros.
     */
    Point();

    /**
     * Another constructor, which sets col and row with given values.
     * @param new_col col coordinate of the point.
     * @param new_row row coordinate of the point.
     */
    Point(short new_col, short new_row);

    short col;
    short row;
} Point;

// Some operators for convenient points operations:
bool operator == (const Point& p1, const Point& p2);
bool operator != (const Point& p1, const Point& p2);
Point operator - (const Point& p1, const Point& p2);
Point operator + (const Point& p1, const Point& p2);
std::ostream& operator << (std::ostream& o, const Point& p);


/**
 * Class representing point of the map.
 * Contains point status (free/barrier/start/finish),
 * and info required for search algorithm - was it visited before and previous point in search in my case.
 */
class mapElement {
public:
    mapElement();
    mapElement(const char& s);

    void setStatus(const char& s);
    char getStatus() const;
    bool isFree() const;

    bool isVisited() const;
    void setVisited();

    bool needToVisit() const;

    void setPrevPoint(const Point& p);
    Point getPrevPoint() const;
private:
    char status;        // Representation of what is on the map in this point.
    bool visited;       // If the point was visited during the search. Defaults to false in all constructors.
    Point prevPoint;    // Coords of previous point in search. Defaults to (0, 0) in all constructors.
};


class map {
public:
    map(const std::string& filename);
    void printMap() const;
    void printSizes() const;

    short getSize() const;

    char pointStatus(const Point& pt) const;
    bool isFree(const Point& pt) const;

    bool isVisited(const Point &pt) const;
    void setVisited(const Point &pt);

    bool needToVisit(const Point& pt) const;
    void setPrevPoint(const Point& current, const Point& prev);
    Point getPrevPoint(const Point& pt) const;

    void markRoute(const std::deque<Point>& route);

    Point getStartPoint() const;
    Point getFinishPoint() const;

private:
    short mapSize_;
    std::vector<std::vector<mapElement>> map_;

    Point start_;
    Point finish_;
};


#endif //PATHFINDER_MAP_H
