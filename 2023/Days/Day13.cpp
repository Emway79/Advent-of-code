#include <iostream>

#include "Day.hpp"
#include "../Libraries/utils.hpp"

namespace AOC2023 {

bool equalColumns(const std::vector<std::string>& grid, int left, int right) {
    for (const std::string& s : grid) {
        if (s[left] != s[right]) {
            return false;
        }
    }

    return true;
}

int64_t findReflection(const std::vector<std::string>& grid, int64_t oldReflection) {
    for (auto row = 0; row < grid.size() - 1; ++row) {
        int above = row;
        int below = row + 1;
        bool correct = true;

        while (above >= 0 && below < grid.size()) {
            if (grid[above] != grid[below]) {
                correct = false;
                break;
            }

            --above;
            ++below;
        }

        if (correct) {
            if (oldReflection != 100 * (row + 1)) {
                return 100 * (row + 1);
            }
        }
    }

    for (auto column = 0; column < grid[0].size() - 1; ++column) {
        int left = column;
        int right = column + 1;
        bool correct = true;

        while (left >= 0 && right < grid[0].size()) {
            if (!equalColumns(grid, left, right)) {
                correct = false;
                break;
            }

            --left;
            ++right;
        }

        if (correct) {
            if (oldReflection != column + 1) {
                return column + 1;
            }
        }
    }

    return - 1;
}

int64_t findSmudgeReflection(std::vector<std::string>& grid) {
    int64_t reflect = findReflection(grid, -1);
    for (int row = 0; row < grid.size(); ++row) {
        for (int column = 0; column < grid[0].size(); ++column) {
            if (grid[row][column] == '.') {
                grid[row][column] = '#';
            } else {
                grid[row][column] = '.';
            }

            int64_t reflection = findReflection(grid, reflect);
            if (reflection != -1) {
                return reflection;
            }

            if (grid[row][column] == '.') {
                grid[row][column] = '#';
            } else {
                grid[row][column] = '.';
            }
        }
    }

    return -1;
}

int64_t solveDay13Part1() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day13.txt");
    int64_t result = 0;

    std::vector<std::string> grid;
    for (std::string& line : lines) {
        if (line.empty()) {
            result += findReflection(grid, -1);

            grid.clear();
        } else {
            grid.push_back(line);
        }
    }
    result += findReflection(grid, -1);

    return result;
}

int64_t solveDay13Part2() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day13.txt");
    int64_t result = 0;

    std::vector<std::string> grid;
    for (std::string& line : lines) {
        if (line.empty()) {
            result += findSmudgeReflection(grid);

            grid.clear();
        } else {
            grid.push_back(line);
        }
    }
    result += findSmudgeReflection(grid);

    return result;
}

}