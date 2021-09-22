//
// Created by Andrew on 9/22/21.
//

#ifndef PATHFINDER_MAP_H
#define PATHFINDER_MAP_H

#include <vector>
#include <string>

// special value returned if point coordinates is out of map range
#define CELL_ACCESS_ERROR 'E'

/**
 * Struct representing point of the map.
 * Contains point's coordinates.
 * Later may be used to store more info.
 */
typedef struct Point {
    /**
     * The default-est constructor possible. Initializes x and y fields with zeros.
     */
    Point();

    /**
     * Another constructor, which sets x and y with given values.
     * @param new_x x coordinate of the point.
     * @param new_y y coordinate of the point.
     */
    Point(unsigned new_x, unsigned new_y);

    unsigned x;
    unsigned y;
} Point;

// Some operators for convenient points operations:
bool operator == (const Point& p1, const Point& p2);
Point operator - (const Point& p1, const Point& p2);
std::ostream& operator << (std::ostream& o, const Point& p);


class map {
public:
    map(const std::string& filename);
    void printMap();
    void checkSize();

    char pointStatus(const Point& pt);
    bool isFree(const Point& pt);

private:
    unsigned mapSize_;
    std::vector<std::vector<char>> map_;

    Point start_;
    Point finish_;
};


#endif //PATHFINDER_MAP_H
