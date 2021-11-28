//
// Created by Yauheni Sharamed on 24.10.2021.
//

#include "finder_a_star.h"
#include <tuple>

inline int heuristic(const Point& a, const Point& b) {
    return abs(a.col - b.col) + abs(a.row - b.row);
}

std::deque<Point> astarPoints::routeFromMap(astarPoints::map& m) {
    std::deque<Point> route;
    Point pt = m.getFinishPoint();
    Point start = m.getStartPoint();
    while(pt != start) {
        route.push_front(pt);
        pt = m.getPrevPoint(pt);
    }
    return route;
}

std::deque<Point> astarPoints::findRoute(astarPoints::map& m) {
    std::deque<Point> route;
    if (m.getStartPoint() == m.getFinishPoint()) {
        // the stupidest case
        return route;
    }

    Point finish = m.getFinishPoint();
    // points we need to visit:
    PriorityQueue nextPoints;
    nextPoints.put(m.getStartPoint(), 0);

    // while we haven't visited all sequences of neighbours
    while(!nextPoints.empty()) {
        auto currentPoint = nextPoints.get();
        m.setVisited(currentPoint);

        if (currentPoint == finish) {
            route = routeFromMap(m);
            break;
        }

        // The point is not the end => visiting four neighbours
        // moving up
        Point nextPoint = currentPoint - Point(0, 1);
        if (nextPoint.row >= 0 && m.needToVisit(nextPoint)) {
            double new_cost = m.getCost(currentPoint) + 1; // cost of each neighbour equals to 1
            if (new_cost < m.getCost(nextPoint) || m.getCost(nextPoint) == 0) {
                m.setCost(nextPoint, new_cost);
                double priority = new_cost + heuristic(nextPoint, finish);
                nextPoints.put(nextPoint, priority);
                m.setPrevPoint(nextPoint, currentPoint);
            }
        }
        // moving down
        nextPoint = currentPoint + Point(0, 1);
        if (nextPoint.row < m.getSize() && m.needToVisit(nextPoint)) {
            double new_cost = m.getCost(currentPoint) + 1; // coast to each neighbour equals to 1
            if (new_cost < m.getCost(nextPoint) || m.getCost(nextPoint) == 0) {
                m.setCost(nextPoint, new_cost);
                double priority = new_cost + heuristic(nextPoint, finish);
                nextPoints.put(nextPoint, priority);
                m.setPrevPoint(nextPoint, currentPoint);
            }
        }

        // moving left
        nextPoint = currentPoint - Point(1, 0);
        if (nextPoint.col >= 0 && m.needToVisit(nextPoint)) {
            double new_cost = m.getCost(currentPoint) + 1; // coast to each neighbour equals to 1
            if (new_cost < m.getCost(nextPoint) || m.getCost(nextPoint) == 0) {
                m.setCost(nextPoint, new_cost);
                double priority = new_cost + heuristic(nextPoint, finish);
                nextPoints.put(nextPoint, priority);
                m.setPrevPoint(nextPoint, currentPoint);
            }
        }
        // moving right
        nextPoint = currentPoint + Point(1, 0);
        if (nextPoint.col < m.getSize() && m.needToVisit(nextPoint)) {
            double new_cost = m.getCost(currentPoint) + 1; // coast to each neighbour equals to 1
            if (new_cost < m.getCost(nextPoint) || m.getCost(nextPoint) == 0) {
                m.setCost(nextPoint, new_cost);
                double priority = new_cost + heuristic(nextPoint, finish);
                nextPoints.put(nextPoint, priority);
                m.setPrevPoint(nextPoint, currentPoint);
            }
        }
    }
    // empty in case there is no route
    // containing route points if there is one
    return route;
}
