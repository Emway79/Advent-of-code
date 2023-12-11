#include "Day.hpp"
#include "../Libraries/utils.hpp"


namespace AOC2023 {

struct Coord {
    int row;
    int column;
};

void expandUniverse(std::vector<std::string>& matrix) {
    for (auto row = 0; row < matrix.size(); ++row) {
        std::string &s = matrix[row];
        bool expand = true;
        for (char& c : s) {
            if (c != '.' && c != '@') {
                expand = false;
                break;
            }
        }
        if (expand) {
            s = std::string(s.size(), '@');
        }
    }

    for (auto column = 0; column < matrix[0].size(); ++column) {
        bool expand = true;
        for (auto& row : matrix) {
            if (row[column] != '.' && row[column] != '@') {
                expand = false;
                break;
            }
        }
        if (expand) {
            for (auto& i : matrix) {
                i[column] = '@';
            }
        }
    }
}

int64_t getDistance(Coord& first, Coord& second, std::vector<std::string>& matrix, int64_t expansion) {
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

    for (auto i = start.row; i < end.row; ++i) {
        if (matrix[i][start.column] == '@') {
            ++spaces;
        }
    }
    for (auto i = start.column; i < end.column; ++i) {
        if (matrix[start.row][i] == '@') {
            ++spaces;
        }
    }

    return abs(vertical) + abs(horizontal) - spaces + (spaces * expansion);
}

int64_t solveDay11Part1() {
    std::vector<std::string> matrix = utils::readFileLines("..\\Resources\\day11.txt");
    expandUniverse(matrix);

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
            result += getDistance(galaxies[i], galaxies[j], matrix, 2);
        }
    }

    return result;
}

int64_t solveDay11Part2() {
    std::vector<std::string> matrix = utils::readFileLines("..\\Resources\\day11.txt");
    expandUniverse(matrix);

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
            result += getDistance(galaxies[i], galaxies[j], matrix, 1000000);
        }
    }

    return result;
}

}