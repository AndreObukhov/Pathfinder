//
// Created by Andrew on 9/22/21.
//

#ifndef PATHFINDER_MAP_H
#define PATHFINDER_MAP_H

#include <vector>
#include <string>
#include <deque>

#include <iostream>
#include <fstream>

#include <random>

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


class mapElem {
public:
    mapElem();
    mapElem(const char& s);
    void setStatus(const char &s);
    char getStatus() const;

    bool isFree() const;

    bool isVisited() const;
    void setVisited();
    bool needToVisit() const;
protected:
    char status;        // Representation of what is on the map in this point.
    bool visited;       // If the point was visited during the search. Defaults to false in all constructors.
};


template<typename T>
class mapT {
public:
    mapT() {
        mapSize_ = 10;
        start_ = Point(1, 0);
        finish_ = Point(9, 9);
        map_.resize(mapSize_, std::vector<T>(mapSize_));
    }

    mapT(const std::string& filename) {
        mapSize_ = 1;
        std::ifstream input;
        input.open(filename);

        input >> mapSize_;
        map_.resize(mapSize_, std::vector<T>(mapSize_));

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

    mapT(const short& size, const int& barrierPercent) {
        mapSize_ = size;

        std::random_device rd;          // only used once to initialise (seed) engine
        std::mt19937 rng(rd());         // random-number engine used (Mersenne-Twister)
        std::uniform_int_distribution<int> uni(0, 100);     // guaranteed unbiased

        map_.resize(size);
        for (int i = 0; i < size; i ++) {
            std::vector<T> line(size);
            for (int j = 0; j < size; j++) {
                int a = uni(rng);
                if (a % 100 < barrierPercent) {
                    line[j].setStatus('#');
                }
            }
            map_[i] = line;
        }
    }

    void printMap() const {
        for (const auto& v: map_ ) {
            for (const auto& el: v) {
                std::cout << el.getStatus() << ' ';
            }
            std::cout << std::endl;
        }
    }

    short getSize() const {
        return mapSize_;
    }

    char pointStatus(const Point& pt) const {
        if (pt.col < mapSize_ && pt.row < mapSize_) {
            return map_[pt.row][pt.col].getStatus();
        } else {
            return CELL_ACCESS_ERROR;
        }
    }

    bool isFree(const Point &pt) const {
        // to avoid accessing unassigned memory
        if (pt.col < mapSize_ && pt.row < mapSize_)
            return map_[pt.row][pt.col].isFree();
        else
            return false;
    }

    bool isVisited(const Point &pt) const {
        return map_[pt.row][pt.col].isVisited();
    }

    void setVisited(const Point &pt) {
        map_[pt.row][pt.col].setVisited();
    }

    bool needToVisit(const Point &pt) const {
        return map_[pt.row][pt.col].needToVisit();
    }

    Point getStartPoint() const {
        return start_;
    }

    Point getFinishPoint() const {
        return finish_;
    }

    void markRoute(const std::deque<Point> &route) {
        for (const Point& pt : route) {
            if (pt != finish_ && pt != start_) {
                map_[pt.row][pt.col].setStatus('*');
            }
        }
    }

protected:
    std::vector<std::vector<T>> map_;
    short mapSize_;
    Point start_;
    Point finish_;
};


namespace bfsPoints {
/**
 * Class representing point of the map.
 * Contains point status (free/barrier/start/finish),
 * and info required for search algorithm - was it visited before and previous point in search in my case.
 */
    class mapElement : public mapElem {
    public:
        void setPrevPoint(const Point &p);
        Point getPrevPoint() const;
    private:
        Point prevPoint;    // Coords of previous point in search. Defaults to (0, 0) in all constructors.
    };

    class map : public mapT<bfsPoints::mapElement> {
    public:
        map(const std::string& filename);
        void setPrevPoint(const Point &current, const Point &prev);
        Point getPrevPoint(const Point &pt) const;
    };
}

namespace bfsInts {
    // ...
}


#endif //PATHFINDER_MAP_H
