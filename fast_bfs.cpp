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
                        this->start_y = i;
                        this->start_x = j;
                    }
                    if (inputSymbol == 'F') {
                        this->finish_y = i;
                        this->finish_x = j;
                    }
                }
            }
        }

    }
}

void SimpleMap::print_start_end() const {
    std::cout << "start: x = " << this->start_x << "; y = " << this->start_y << "\nfinish: x = " << this->finish_x
              << "; y = " << this->finish_y << std::endl;
}

std::vector<std::tuple<int, int>> SimpleMap::bfs(){
    int x,y;
    int dx, dy;
    int nx, ny;
    int curr_len;

    if (this->start_x == this->finish_x && this->start_y == this->finish_y){
        return this->steps;
    }

    this->field[this->start_y][this->start_x] = 0;
    this->queue.emplace_back(this->start_x, this->start_y);
    while (!this->queue.empty()){
        std::tie(x, y) = this->queue.front();
        this->queue.pop_front();
        curr_len = this->field[y][x] + 1;
        for (int i = 0; i < 4; i++) {
            std::tie(dx, dy) = this->deltas[i];
            nx = x + dx;
            ny = y + dy;
            if (this->field[ny][nx] != -1 && this->field[ny][nx] > curr_len){
                this->field[ny][nx] = curr_len;
                this->queue.emplace_back(nx, ny);
                if (this->finish_x == nx && this->finish_y == ny){ // построение пути
                    return this->build_path();
                }
            }
        }
    }
    this->steps.emplace_back(-1,-1); // если пути нет
    return this->steps;
}

std::vector<std::tuple<int, int>> SimpleMap::build_path(){
    int x = this->finish_x, y = this->finish_y;
    int dx, dy;
    int nx, ny;
    this->steps.emplace_back(x, y);
    while(this->field[y][x] != 0){
        for (int i = 0; i < 4; i++) {
            std::tie(dx, dy) = this->deltas[i];
            nx = x + dx;
            ny = y + dy;
            if (this->field[ny][nx] < this->field[y][x] && this->field[ny][nx] != -1){
                this->steps.emplace_back(nx, ny);
                x = nx;
                y = ny;
                break;
            }
        }
    }
    return this->steps;
}

int SimpleMap::path_len() {
    return this->field[this->finish_y][this->finish_x];
}

void SimpleMap::print_steps() {
    auto iter = this->steps.rbegin();
    int i = 1;
    int x, y;
    while(iter != this->steps.rend()){
        std::tie(x, y) = *iter;
        std::cout << i << ": x = " << x << "; y = " << y << std::endl;
        ++iter;
        i++;
    }
}
