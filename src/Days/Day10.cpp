#include <iostream>
#include <ostream>
#include <queue>
#include "Day.hpp"
#include "../Libraries/utils.hpp"


namespace AOC2023 {

struct Coord {
    int row;
    int column;
};

Coord findStart(const std::vector<std::string>& matrix) {
    for (auto row = 0; row < matrix.size(); ++row) {
        for (auto column = 0; column < matrix[0].size(); ++column) {
            if (matrix[row][column] == 'S') {
                return {row, column};
            }
        }
    }
    return {};
}

void findNextPipe(Coord& current, Coord& prev, const std::vector<std::string>& matrix) {
    if (matrix[current.row][current.column] == 'S') {
        char up = matrix[current.row - 1][current.column];
        char down = matrix[current.row + 1][current.column];
        char right = matrix[current.row][current.column + 1];

        if (up == '7' || up == '|' || up == 'F') {
            --current.row;
        } else if (down == '|' || down == 'L' || down == 'J') {
            ++current.row;
        } else if (right == '-' || right == '7' || right == 'J') {
            ++current.column;
        } else {
            --current.column;
        }

    } else {
        switch (matrix[current.row][current.column]) {
            case '-': {
                if (prev.column < current.column) {
                    ++prev.column;
                    ++current.column;
                } else {
                    --prev.column;
                    --current.column;
                }
                break;
            }
            case '|': {
                if (prev.row < current.row) {
                    ++prev.row;
                    ++current.row;
                } else {
                    --prev.row;
                    --current.row;
                }
                break;
            }
            case 'J': {
                if (prev.row < current.row) {
                    ++prev.row;
                    --current.column;
                } else {
                    ++prev.column;
                    --current.row;
                }
                break;
            }
            case 'F': {
                if (prev.row > current.row) {
                    --prev.row;
                    ++current.column;
                } else {
                    --prev.column;
                    ++current.row;
                }
                break;
            }
            case '7': {
                if (prev.column < current.column) {
                    ++prev.column;
                    ++current.row;
                } else {
                    --prev.row;
                    --current.column;
                }
                break;
            }
            case 'L': {
                if (prev.row < current.row) {
                    ++prev.row;
                    ++current.column;
                } else {
                    --prev.column;
                    --current.row;
                }
                break;
            }
        }
    }
}

std::vector<std::string> expandMatrix(std::vector<std::string>& matrix) {
    std::vector<std::string> result;
    for (std::string& s : matrix) {
        std::string top;
        std::string bot;
        for (char& c : s) {
            switch (c) {
                case '-': {
                    top += "--";
                    bot += "##";
                    break;
                }
                case '|': {
                    top += "|#";
                    bot += "|#";
                    break;
                }
                case 'F': {
                    top += "F-";
                    bot += "|#";
                    break;
                }
                case 'L': {
                    top += "L-";
                    bot += "##";
                    break;
                }
                case 'J': {
                    top += "J#";
                    bot += "##";
                    break;
                }
                case '7': {
                    top += "7#";
                    bot += "|#";
                    break;
                }
                case 'S': {
                    top += "S-";
                    bot += "##";
                    break;
                }
                default: {
                    top += c;
                    top += '#';
                    bot += "##";
                    break;
                }
            }
        }

        result.push_back(top);
        result.push_back(bot);
    }

    return result;
}

void floodFill(std::vector<std::string>& matrix) {
    std::queue<int> queue;
    queue.push(0);
    queue.push(0);

    while (!queue.empty()) {
        int row = queue.front();
        queue.pop();
        int column = queue.front();
        queue.pop();
        if (row < 0 || row >= matrix.size() || column < 0 || column >= matrix[0].size()) {
            continue;
        }

        if (matrix[row][column] != 'S') {
            matrix[row][column] = 'S';
            queue.push(row - 1);
            queue.push(column);
            queue.push(row + 1);
            queue.push(column);
            queue.push(row);
            queue.push(column - 1);
            queue.push(row);
            queue.push(column + 1);
        }
    }
}


int64_t solveDay10Part1() {
    std::vector<std::string> matrix = utils::readFileLines("..\\src\\Resources\\day10.txt");
    Coord current = findStart(matrix);

    int64_t result = 0;
    Coord previous = current;
    do {
        findNextPipe(current, previous, matrix);
        ++result;

    } while(matrix[current.row][current.column] != 'S');


    return result / 2;
}

int64_t solveDay10Part2() {
    std::vector<std::string> lines = utils::readFileLines("..\\src\\Resources\\day10.txt");
    std::vector<std::string> matrix = expandMatrix(lines);

    Coord current = findStart(matrix);
    Coord previous = current;
    do {
        findNextPipe(current, previous, matrix);
        matrix[previous.row][previous.column] = 'S';

    } while(matrix[current.row][current.column] != 'S');

    floodFill(matrix);

    int64_t result = 0;
    for (auto i = 0; i < matrix.size(); i += 2) {
        for (auto j = 0; j < matrix[0].size(); j += 2) {
            char c = matrix[i][j];
            if (c != 'S' && c != '#') {
                ++result;
            }
        }
    }

    return result;
}

}