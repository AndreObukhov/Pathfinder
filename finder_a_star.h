//
// Created by Yauheni Sharamed on 24.10.2021.
//

#ifndef PATHFINDER_FINDER_A_STAR_H
#define PATHFINDER_FINDER_A_STAR_H

#include <deque>
#include <queue>
#include "map.h"

//bool operator<(const std::pair<int, Point>& lhs, const std::pair<int, Point>& rhs) {
//    return lhs.first < rhs.first;
//}

namespace astarPoints {
    std::deque<Point> routeFromMap(map &m);
    std::deque<Point> findRoute(map &m);

    struct PriorityQueue {
        typedef std::pair<int, Point> PQElement;

        struct PrCmp
        {
            bool operator()(const PQElement& lhs, const PQElement& rhs) const
            {
                return lhs.first < rhs.first;
            }
        };

        std::priority_queue<PQElement, std::vector<PQElement>, PrCmp> elements;

        inline bool empty() const {
            return elements.empty();
        }

        inline void put(Point item, int priority) {
            elements.emplace(std::pair<int, Point>(priority, item));
        }

        inline Point get() {
            Point best_item = elements.top().second;
            elements.pop();
            return best_item;
        }
    };

}



namespace astarInts {
    // ...
}



#endif //PATHFINDER_FINDER_A_STAR_H
