//
// Created by Andrew on 10/3/21.
//

#ifndef PATHFINDER_FINDER_BFS_H
#define PATHFINDER_FINDER_BFS_H

#include <deque>
#include "map.h"

namespace bfsPoints {
/**
 * Builds route (sequence of points) from a map with marked steps (previous points).
 * @param m - map with marked steps.
 * @return route - std::deque of points.
 */
    std::deque<Point> routeFromMap(map &m);

    void addToQueue(const Point& currentPoint, const Point& nextPoint,
                    map& m, std::deque<Point>& nextPoints);

/**
 * Finds route (sequence of points) on a map with marked start, finish and barriers.
 * @param m - map.
 * @return route - std::deque of points. Empty in case there is no route.
 */
    std::deque<Point> findRoute(map &m);
}

namespace bfsInts {
    std::deque<Point> routeFromMap(map &m);
    std::deque<Point> findRoute(map &m);

    Point checkNeighbours(const int& dist, const Point &p, const map &m);
    void addToQueue(const Point& currentPoint, const Point& nextPoint,
                    bfsInts::map& m, std::deque<Point>& nextPoints);
}

#endif //PATHFINDER_FINDER_BFS_H
