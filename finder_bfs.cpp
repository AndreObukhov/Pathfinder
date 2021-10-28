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

void bfsPoints::addToQueue(const Point& currentPoint, const Point& nextPoint,
                bfsPoints::map& m, std::deque<Point>& nextPoints) {
    // to avoid visiting one point from many neighbours
    m.setVisited(nextPoint);
    // previous point for the next step is our current point
    m.setPrevPoint(nextPoint, currentPoint);
    nextPoints.push_back(nextPoint);
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
            addToQueue(currentPoint, nextPoint, m, nextPoints);
        }
        // moving down
        nextPoint = currentPoint + Point(0, 1);
        if (nextPoint.row < m.getSize() && m.needToVisit(nextPoint)) {
            addToQueue(currentPoint, nextPoint, m, nextPoints);
        }

        // moving left
        nextPoint = currentPoint - Point(1, 0);
        if (nextPoint.col >= 0 && m.needToVisit(nextPoint)) {
            addToQueue(currentPoint, nextPoint, m, nextPoints);
        }
        // moving right
        nextPoint = currentPoint + Point(1, 0);
        if (nextPoint.col < m.getSize() && m.needToVisit(nextPoint)) {
            addToQueue(currentPoint, nextPoint, m, nextPoints);
        }

        nextPoints.pop_front();
    }
    // empty in case there is no route
    // containing route points if there is one
    return route;
}

Point bfsInts::checkNeighbours(const int& dist, const Point& p, const bfsInts::map& m) {
    Point next = p - Point(1, 0);
    if (next.col >= 0) {
        if (dist == m.getDist(next))
            return next;
    }

    next = p + Point(1, 0);
    if (next.col < m.getSize()) {
        if (dist == m.getDist(next))
            return next;
    }

    next = p + Point(0, 1);
    if (next.row < m.getSize()) {
        if (dist == m.getDist(next))
            return next;
    }

    next = p - Point(0, 1);
    if (next.row >= 0) {
        if (dist == m.getDist(next))
            return next;
    }
}

std::deque<Point> bfsInts::routeFromMap(bfsInts::map& m) {
    std::deque<Point> route;
    Point current = m.getFinishPoint();
    int distance = m.getDist(current);
    while (current !=  m.getStartPoint()) {
        distance --;
        Point next = checkNeighbours(distance, current, m);
        current = next;
        route.push_front(current);
    }
    return route;
}

void bfsInts::addToQueue(const Point& currentPoint, const Point& nextPoint,
                         bfsInts::map& m, std::deque<Point>& nextPoints) {
    // to avoid visiting one point from many neighbours
    m.setVisited(nextPoint);
    // previous point for the next step is our current point
    m.setDist(nextPoint, m.getDist(currentPoint) + 1);
    nextPoints.push_back(nextPoint);
}

std::deque<Point> bfsInts::findRoute(bfsInts::map& m) {
    std::deque<Point> route;
    if (m.getStartPoint() == m.getFinishPoint()) {
        // the stupidest case
        return route;
    }
    m.setDist(m.getStartPoint(), 0);

    Point finish = m.getFinishPoint();
    // points we need to visit:
    std::deque<Point> nextPoints;
    nextPoints.push_back(m.getStartPoint());
    // while we haven't visited all sequences of neighbours
    while(!nextPoints.empty()) {
        Point currentPoint = nextPoints.front();
        m.setVisited(currentPoint);

        if (currentPoint == finish) {
            // std::cout << "GOING BACK" << std::endl;
            route = routeFromMap(m);
            break;
        }

        // The point is not the end => visiting four neighbours
        // moving up
        Point nextPoint = currentPoint - Point(0, 1);
        if (nextPoint.row >= 0 && m.needToVisit(nextPoint)) {
            addToQueue(currentPoint, nextPoint, m, nextPoints);
        }
        // moving down
        nextPoint = currentPoint + Point(0, 1);
        if (nextPoint.row < m.getSize() && m.needToVisit(nextPoint)) {
            addToQueue(currentPoint, nextPoint, m, nextPoints);
        }

        // moving left
        nextPoint = currentPoint - Point(1, 0);
        if (nextPoint.col >= 0 && m.needToVisit(nextPoint)) {
            addToQueue(currentPoint, nextPoint, m, nextPoints);
        }
        // moving right
        nextPoint = currentPoint + Point(1, 0);
        if (nextPoint.col < m.getSize() && m.needToVisit(nextPoint)) {
            addToQueue(currentPoint, nextPoint, m, nextPoints);
        }

        nextPoints.pop_front();
    }

    return route;
}
