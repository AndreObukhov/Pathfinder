//
// Created by Andrew on 10/5/21.
//

#include "map_generator.h"

void generateMap(const int& size, const int& threshold, const std::string& filename) {
    std::ofstream outFile;
    std::string line;

    std::random_device rd;          // only used once to initialise (seed) engine
    std::mt19937 rng(rd());         // random-number engine used (Mersenne-Twister)
    std::uniform_int_distribution<int> uni(0, 100);     // guaranteed unbiased

    outFile.open(filename);
    outFile << size << std::endl;
    for(int i = 0; i < size; i ++) {
        for(int j = 0; j < size; j ++) {
            int a = uni(rng);
            if (a % 100 < threshold) {
                line.push_back('#');
            } else {
                line.push_back('.');
            }
        }
        outFile << line << std::endl;
        line.clear();
    }
    outFile.close();
}
