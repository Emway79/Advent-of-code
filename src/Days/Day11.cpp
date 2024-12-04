#include "Day.hpp"
#include "../Libraries/utils.hpp"

namespace AOC2023 {

struct Coord {
    int row;
    int column;
};

std::vector<int> expandUniverseRows(std::vector<std::string>& matrix) {
    std::vector<int> result;
    for (auto row = 0; row < matrix.size(); ++row) {
        std::string &s = matrix[row];
        bool expand = true;
        for (char &c: s) {
            if (c != '.') {
                expand = false;
                break;
            }
        }
        if (expand) {
            result.push_back(row);
        }
    }

    return result;
}

std::vector<int> expandUniverseColumns(std::vector<std::string>& matrix) {
    std::vector<int> result;
    for (auto column = 0; column < matrix[0].size(); ++column) {
        bool expand = true;
        for (auto& row : matrix) {
            if (row[column] != '.') {
                expand = false;
                break;
            }
        }
        if (expand) {
            result.push_back(column);
        }
    }

    return result;
}

int64_t getDistance(Coord& first, Coord& second, std::vector<int>& rows, std::vector<int>& columns, int64_t expansion) {
    int64_t spaces = 0;
    int vertical = abs(first.row - second.row);
    int horizontal = abs(first.column - second.column);

    Coord start{first.row, first.column};
    Coord end{second.row, second.column};
    if (second.row < first.row) {
        start.row = second.row;
        end.row = first.row;
    }
    if (second.column < first.column) {
        start.column = second.column;
        end.column = first.column;
    }

    for (auto column : columns) {
        if (column > start.column && column < end.column) {
            ++spaces;
        }
    }

    for (auto row : rows) {
        if (row > start.row && row < end.row) {
            ++spaces;
        }
    }


    return abs(vertical) + abs(horizontal) - spaces + (spaces * expansion);
}

int64_t solveDay11Part1() {
    std::vector<std::string> matrix = utils::readFileLines("..\\src\\Resources\\day11.txt");
    std::vector<int> rows = expandUniverseRows(matrix);
    std::vector<int> columns = expandUniverseColumns(matrix);

    std::vector<Coord> galaxies;
    for (auto row = 0; row < matrix.size(); ++row) {
        for (auto column = 0; column < matrix[0].size(); ++column) {
            if (matrix[row][column] == '#') {
                galaxies.push_back({row, column});
            }
        }
    }

    int64_t result = 0;
    for (auto i = 0; i < galaxies.size() - 1; ++i) {
        for (auto j = i + 1; j < galaxies.size(); ++j) {
            result += getDistance(galaxies[i], galaxies[j], rows, columns, 2);
        }
    }

    return result;
}

int64_t solveDay11Part2() {
    std::vector<std::string> matrix = utils::readFileLines("..\\src\\Resources\\day11.txt");
    std::vector<int> rows = expandUniverseRows(matrix);
    std::vector<int> columns = expandUniverseColumns(matrix);

    std::vector<Coord> galaxies;
    for (auto row = 0; row < matrix.size(); ++row) {
        for (auto column = 0; column < matrix[0].size(); ++column) {
            if (matrix[row][column] == '#') {
                galaxies.push_back({row, column});
            }
        }
    }

    int64_t result = 0;
    for (auto i = 0; i < galaxies.size() - 1; ++i) {
        for (auto j = i + 1; j < galaxies.size(); ++j) {
            result += getDistance(galaxies[i], galaxies[j], rows, columns, 1000000);
        }
    }

    return result;
}

}