#include <unordered_map>
#include <iostream>

#include "Day.hpp"
#include "../Libraries/utils.hpp"

namespace AOC2023 {

void tiltNorth(std::vector<std::string>& rocks) {
    for (auto row = 1; row < rocks.size(); ++row) {
        for (auto column = 0; column < rocks[0].size(); ++column) {
            if (rocks[row][column] == 'O') {
                rocks[row][column] = '.';
                int north = row - 1;
                while (north >= 0 && rocks[north][column] == '.') {
                    --north;
                }

                rocks[north + 1][column] = 'O';
            }
        }
    }
}

void tiltSouth(std::vector<std::string>& rocks) {
    for (int row = rocks.size() - 2; row >= 0; --row) {
        for (auto column = 0; column < rocks[0].size(); ++column) {
            if (rocks[row][column] == 'O') {
                rocks[row][column] = '.';
                int south = row + 1;
                while (south < rocks.size() && rocks[south][column] == '.') {
                    ++south;
                }

                rocks[south - 1][column] = 'O';
            }
        }
    }
}

void tiltWest(std::vector<std::string>& rocks) {
    for (auto column = 1; column < rocks[0].size(); ++column) {
        for (auto row = 0; row < rocks.size(); ++row) {
            if (rocks[row][column] == 'O') {
                rocks[row][column] = '.';
                int west = column - 1;
                while (west >= 0 && rocks[row][west] == '.') {
                    --west;
                }

                rocks[row][west + 1] = 'O';
            }
        }
    }
}

void tiltEast(std::vector<std::string>& rocks) {
    for (int column = rocks[0].size() - 2; column >= 0; --column) {
        for (auto row = 0; row < rocks.size(); ++row) {
            if (rocks[row][column] == 'O') {
                rocks[row][column] = '.';
                int east = column + 1;
                while (east < rocks.size() && rocks[row][east] == '.') {
                    ++east;
                }

                rocks[row][east - 1] = 'O';
            }
        }
    }
}

int64_t countNorthSupportLoad(const std::vector<std::string>& rocks) {
    int64_t totalLoad = 0;

    for (auto row = 0; row < rocks.size(); ++row) {
        for (auto column = 0; column < rocks[0].size(); ++column) {
            if (rocks[row][column] == 'O') {
                totalLoad += rocks.size() - row;
            }
        }
    }

    return totalLoad;
}

int64_t hashGrid(const std::vector<std::string>& rocks) {
    int64_t result = 0;
    for (auto row = 0; row < rocks.size(); ++row) {
        for (auto column = 0; column < rocks[0].size(); ++column) {
            result += (row + 1) * ((column + 1) * 100) * rocks[row][column];
        }
    }

    return result;
}

void tiltGrid(std::vector<std::string>& rocks) {
    tiltNorth(rocks);
    tiltWest(rocks);
    tiltSouth(rocks);
    tiltEast(rocks);
}


int64_t solveDay14Part1() {
    std::vector<std::string> rocks = utils::readFileLines("..\\src\\Resources\\day14.txt");
    tiltNorth(rocks);

    int64_t result = countNorthSupportLoad(rocks);

    return result;
}

int64_t solveDay14Part2() {
    std::vector<std::string> rocks = utils::readFileLines("..\\src\\Resources\\day14.txt");
    std::unordered_map<int64_t, int64_t> hashes;

    int64_t cycleOffset = -1;
    int64_t cycleLength = -1;
    for (int64_t cycle = 1; cycle <= 1000000000; ++cycle) {
        tiltGrid(rocks);

        int64_t hash = hashGrid(rocks);
        if (hashes.contains(hash)) {
            cycleOffset = hashes[hash];
            cycleLength = cycle - cycleOffset;
            break;
        }

        hashes.insert({hash, cycle});
    }

    int64_t missingCycles = 1000000000 - (1000000000 - cycleOffset) % cycleLength;
    for (int64_t i = missingCycles; i < 1000000000; ++i) {
        tiltGrid(rocks);
    }

    int64_t result = countNorthSupportLoad(rocks);

    return result;
}

}