#include "Day.hpp"
#include "../Libraries/utils.hpp"


namespace AOC2023 {


struct Number {
    int n;
    int beginIndex;
    int endIndex;
};


int64_t solveDay3Part1() {
    std::vector<std::string> matrix = utils::readFileLines("..\\Resources\\day3.txt");
    int64_t result = 0;
    size_t width = matrix[0].size();
    size_t length = matrix.size();

    for (auto row = 0; row < length; ++row) {
        int num = 0;
        int add = false;
        for (auto column = 0; column < width; ++column) {
            if (isdigit(matrix[row][column])) {
                if (num != 0) {
                    num *= 10;
                }
                num += matrix[row][column] - '0';

                if (column != 0 && row != 0) {
                    add |= !isdigit(matrix[row - 1][column - 1]) && matrix[row - 1][column - 1] != '.';
                }
                if (column != 0) {
                    add |= !isdigit(matrix[row][column - 1]) && matrix[row][column - 1] != '.';
                }
                if (column != 0 && row != length - 1) {
                    add |= !isdigit(matrix[row + 1][column - 1]) && matrix[row + 1][column - 1] != '.';
                }
                if (column != width - 1 && row != 0) {
                    add |= !isdigit(matrix[row - 1][column + 1]) && matrix[row - 1][column + 1] != '.';
                }
                if (column != width - 1) {
                    add |= !isdigit(matrix[row][column + 1]) && matrix[row][column + 1] != '.';
                }
                if (column != width - 1 && row != length - 1) {
                    add |= !isdigit(matrix[row + 1][column + 1]) && matrix[row + 1][column + 1] != '.';
                }
                if (row != 0) {
                    add |= !isdigit(matrix[row - 1][column]) && matrix[row - 1][column] != '.';
                }
                if (row != length - 1) {
                    add |= !isdigit(matrix[row + 1][column]) && matrix[row + 1][column] != '.';
                }

            }

            if (!isdigit(matrix[row][column]) || column == width - 1) {
                if (add) {
                    result += num;
                }
                add = false;
                num = 0;
            }
        }
    }

    return result;
}

int64_t solveDay3Part2() {
    std::vector<std::string> matrix = utils::readFileLines("..\\Resources\\day3.txt");
    std::vector<std::vector<Number>> numbers;

    int64_t result = 0;
    size_t width = matrix[0].size();
    size_t length = matrix.size();

    for (auto row = 0; row < length; ++row) {
        std::vector<Number> line;
        Number num{};
        for (auto column = 0; column < width; ++column) {
            if (isdigit(matrix[row][column])) {
                if (num.n != 0) {
                    num.n *= 10;
                } else {
                    num.beginIndex = column;
                }
                num.n += matrix[row][column] - '0';
            }

            if (!isdigit(matrix[row][column]) || column == width - 1) {
                if (num.n != 0) {
                    num.endIndex = column - 1;
                    line.push_back(num);
                    Number newNumber{};
                    num = newNumber;
                }
            }
        }

        numbers.push_back(line);
    }

    for (auto row = 0; row < length; ++row) {
        for (auto column = 0; column < width; ++column) {
            if (matrix[row][column] == '*') {
                int gears = 0;
                int ratio = 1;
                for (Number n : numbers[row - 1]) {
                    if (n.beginIndex <= column + 1 && n.endIndex >= column - 1) {
                        ++gears;
                        ratio *= n.n;
                    }
                }
                for (Number n : numbers[row]) {
                    if (n.beginIndex <= column + 1 && n.endIndex >= column - 1) {
                        ++gears;
                        ratio *= n.n;
                    }
                }
                for (Number n : numbers[row + 1]) {
                    if (n.beginIndex <= column + 1 && n.endIndex >= column - 1) {
                        ++gears;
                        ratio *= n.n;
                    }
                }

                if (gears == 2) {
                    result += ratio;
                }
            }
        }
    }

    return result;
}

}