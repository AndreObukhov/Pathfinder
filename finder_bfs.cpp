//
// Created by Andrew on 10/3/21.
//

#include "finder_bfs.h"

std::deque<Point> bfsPoints::routeFromMap(bfsPoints::map& m) {
    std::deque<Point> route;
    Point pt = m.getFinishPoint();
    Point start = m.getStartPoint();
    while(pt != start) {
        route.push_front(pt);
        pt = m.getPrevPoint(pt);
    }
    return route;
}

std::deque<Point> bfsPoints::findRoute(bfsPoints::map& m) {
    std::deque<Point> route;
    if (m.getStartPoint() == m.getFinishPoint()) {
        // the stupidest case
        return route;
    }

    Point finish = m.getFinishPoint();
    // points we need to visit:
    std::deque<Point> nextPoints;
    nextPoints.push_back(m.getStartPoint());

    // while we haven't visited all sequences of neighbours
    while(!nextPoints.empty()) {
        Point currentPoint = nextPoints.front();
        m.setVisited(currentPoint);

        if (currentPoint == finish) {
            route = routeFromMap(m);
            break;
        }

        // The point is not the end => visiting four neighbours
        // moving up
        Point nextPoint = currentPoint - Point(0, 1);
        if (nextPoint.row >= 0 && m.needToVisit(nextPoint)) {
            // to avoid visiting one point from many neighbours
            m.setVisited(nextPoint);
            // previous point for the next step is our current point
            m.setPrevPoint(nextPoint, currentPoint);
            nextPoints.push_back(nextPoint);
        }
        // moving down
        nextPoint = currentPoint + Point(0, 1);
        if (nextPoint.row < m.getSize() && m.needToVisit(nextPoint)) {
            // to avoid visiting one point from many neighbours
            m.setVisited(nextPoint);
            // previous point for the next step is our current point
            m.setPrevPoint(nextPoint, currentPoint);
            nextPoints.push_back(nextPoint);
        }

        // moving left
        nextPoint = currentPoint - Point(1, 0);
        if (nextPoint.col >= 0 && m.needToVisit(nextPoint)) {
            // to avoid visiting one point from many neighbours
            m.setVisited(nextPoint);
            // previous point for the next step is our current point
            m.setPrevPoint(nextPoint, currentPoint);
            nextPoints.push_back(nextPoint);
        }
        // moving right
        nextPoint = currentPoint + Point(1, 0);
        if (nextPoint.col < m.getSize() && m.needToVisit(nextPoint)) {
            // to avoid visiting one point from many neighbours
            m.setVisited(nextPoint);
            // previous point for the next step is our current point
            m.setPrevPoint(nextPoint, currentPoint);
            nextPoints.push_back(nextPoint);
        }

        nextPoints.pop_front();
    }
    // empty in case there is no route
    // containing route points if there is one
    return route;
}

