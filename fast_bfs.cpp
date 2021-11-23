#include "fast_bfs.h"
#include <climits>

SimpleMap::SimpleMap(const std::string &filename) {
    this->map_size = 0;
    char inputSymbol;
    std::ifstream infile(filename);
    infile >> this->map_size;
    this->field = (int **) malloc(sizeof(int *) * (this->map_size + 2)); // карта с бортиками
    for (int i = 0; i < this->map_size + 2; i++) {
        this->field[i] = (int *) malloc(sizeof(int) * (this->map_size + 2));
        if (i == 0 || i == this->map_size + 1) {
            for (int j = 0; j < this->map_size + 2; j++) { // верхний и нижний бортики
                this->field[i][j] = -1;
            }
        } else {
            this->field[i][0] = -1; // левый
            this->field[i][this->map_size + 1] = -1; // и правый бортики
            for (int j = 1; j < this->map_size + 1; j++) { // само поле
                infile >> inputSymbol;
                if (inputSymbol == '#') {
                    this->field[i][j] = -1;
                } else {
                    this->field[i][j] = INT_MAX;
                    if (inputSymbol == 'S') {
//                        this->start_y = i;
//                        this->start_x = j;
                        this->startPoint = Point(j,i);
                    }
                    if (inputSymbol == 'F') {
//                        this->finish_y = i;
//                        this->finish_x = j;
                        this->finishPoint = Point(j,i);
                    }
                }
            }
        }
    }
    infile.close();
}

SimpleMap::~SimpleMap() {
    for (int i = 0; i < this->map_size + 2; i++) {
        free(this->field[i]);
    }
    free(this->field);
}

void SimpleMap::print_start_end() const {
    std::cout << "start: x = " << this->startPoint.col << "; y = " << this->startPoint.row << "\nfinish: x = " << this->finishPoint.col
              << "; y = " << this->finishPoint.row << std::endl;
}

std::vector<Point> SimpleMap::bfs(){
    struct Point point;
    struct Point dPoint;
    struct Point nPoint;
    int curr_len;

    if (this->startPoint == this->finishPoint){
        return this->steps;
    }

    this->field[this->startPoint.row][this->startPoint.col] = 0;
    this->queue.push_back(this->startPoint);
    while (!this->queue.empty()){
        point = this->queue.front();
        this->queue.pop_front();
        curr_len = this->field[point.row][point.col] + 1;
        for (int i = 0; i < 4; i++) {
            dPoint = this->deltas[i];
            nPoint = point + dPoint;
            if (this->field[nPoint.row][nPoint.col] != -1 && this->field[nPoint.row][nPoint.col] > curr_len){
                this->field[nPoint.row][nPoint.col] = curr_len;
                this->queue.emplace_back(nPoint.col, nPoint.row);
                if (nPoint == this->finishPoint){ // построение пути
                    return this->build_path();
                }
            }
        }
    }
    this->steps.emplace_back(-1,-1); // если пути нет
    return this->steps;
}

std::vector<Point> SimpleMap::build_path(){
    struct Point point = this->finishPoint;
    struct Point dPoint;
    struct Point nPoint;
    this->steps.push_back(point);
    while(this->field[point.row][point.col] != 0){
        for (int i = 0; i < 4; i++) {
            dPoint = this->deltas[i];
            nPoint = point + dPoint;
            if (this->field[nPoint.row][nPoint.col] < this->field[point.row][point.col] &&
            this->field[nPoint.row][nPoint.col] != -1){
                this->steps.push_back(nPoint);
                point = nPoint;
                break;
            }
        }
    }
    return this->steps;
}

int SimpleMap::path_len() {
    return this->field[this->finishPoint.row][this->finishPoint.col];
}

void SimpleMap::print_steps() {
    auto iter = this->steps.rbegin();
    int i = 1;
    struct Point point;
    while(iter != this->steps.rend()){
        point = *iter;
        std::cout << i << ": x = " << point.col << "; y = " << point.row << std::endl;
        ++iter;
        i++;
    }
}
