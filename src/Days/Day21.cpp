#include <iostream>
#include <queue>

#include "Day.hpp"
#include "../Libraries/utils.hpp"


namespace AOC2023 {

struct Coord {
    int row;
    int column;
};

void setStartState(std::vector<std::vector<int64_t>>& states, std::vector<std::string>& grid) {
    for (int row = 0; row < grid.size(); ++row) {
        for (int column = 0; column < grid[0].size(); ++column) {
            if (grid[row][column] == '#') {
                states[row][column] = INT64_MAX;
            } else if (grid[row][column] == 'S') {
                grid[row][column] = '.';
                states[row][column] = 1;
            }
        }
    }
}

void calculateDistance(std::vector<std::vector<int64_t>>& states) {
    std::vector<Coord> toAdd;

    for (int row = 0; row < states.size(); ++row) {
        for (int column = 0; column < states[0].size(); ++column) {
            if (states[row][column] == 1) {
                toAdd.push_back({row - 1, column});
                toAdd.push_back({row + 1, column});
                toAdd.push_back({row, column - 1});
                toAdd.push_back({row, column + 1});
                states[row][column] = 0;
                goto findBreak;
            }
        }
    }
    findBreak:

    int64_t distance = 1;
    while (!toAdd.empty()) {
        std::vector<Coord> next;
        for (Coord &coord: toAdd) {
            if (coord.row < 0 || coord.row >= states.size() || coord.column < 0 || coord.column >= states[0].size()) {
                continue;
            }

            if (states[coord.row][coord.column] == 0) {
                next.push_back({coord.row - 1, coord.column});
                next.push_back({coord.row + 1, coord.column});
                next.push_back({coord.row, coord.column - 1});
                next.push_back({coord.row, coord.column + 1});
                states[coord.row][coord.column] = distance;
            }
        }
        ++distance;
        toAdd = next;
    }
}


int64_t solveDay21Part1() {
    std::vector<std::string> grid = utils::readFileLines("..\\src\\Resources\\day21.txt");
    std::vector<std::vector<int64_t>> states(grid.size(), std::vector<int64_t>(grid[0].size(), 0));
    setStartState(states, grid);
    calculateDistance(states);

    int64_t result = 0;
    for (int row = 0; row < states.size(); ++row) {
        for (int column = 0; column < states[0].size(); ++column) {
            if (states[row][column] <= 64 && states[row][column] % 2 == 0) {
                grid[row][column] = 'O';
                ++result;
            }
        }
    }

    for (auto& v : grid) {
        std::cout << v << std::endl;
    }

    return result;
}

int64_t solveDay21Part2() {
    std::vector<std::string> grid = utils::readFileLines("..\\src\\Resources\\day21.txt");
    std::vector<std::vector<int64_t>> states(grid.size(), std::vector<int64_t>(grid[0].size(), 0));
    setStartState(states, grid);

    calculateDistance(states);

    return 0;
}

}