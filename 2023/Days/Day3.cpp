#include "Day.hpp"
#include "../Libraries/utils.hpp"


namespace AOC2023 {

struct number {
    int n;
    int beginIndex;
    int endIndex;
};

int64_t solveDay3Part1() {
    std::vector<std::string> matrix = utils::readFileLines("..\\Resources\\day3.txt");
    int64_t result = 0;
    int width = matrix[0].size();
    int length = matrix.size();

    for (int y = 0; y < length; ++y) {
        int num = 0;
        int add = false;
        for (int x = 0; x < width; ++x) {
            if (isdigit(matrix[y][x])) {
                if (num != 0) {
                    num *= 10;
                }
                num += matrix[y][x] - '0';

                if (x != 0 && y != 0) {
                    add |= !isdigit(matrix[y - 1][x - 1]) && matrix[y - 1][x - 1] != '.';
                }
                if (x != 0) {
                    add |= !isdigit(matrix[y][x - 1]) && matrix[y][x - 1] != '.';
                }
                if (x != 0 && y != length - 1) {
                    add |= !isdigit(matrix[y + 1][x - 1]) && matrix[y + 1][x - 1] != '.';
                }
                if (x != width - 1 && y != 0) {
                    add |= !isdigit(matrix[y - 1][x + 1]) && matrix[y - 1][x + 1] != '.';
                }
                if (x != width - 1) {
                    add |= !isdigit(matrix[y][x + 1]) && matrix[y][x + 1] != '.';
                }
                if (x != width - 1 && y != length - 1) {
                    add |= !isdigit(matrix[y + 1][x + 1]) && matrix[y + 1][x + 1] != '.';
                }
                if (y != 0) {
                    add |= !isdigit(matrix[y - 1][x]) && matrix[y - 1][x] != '.';
                }
                if (y != length - 1) {
                    add |= !isdigit(matrix[y + 1][x]) && matrix[y + 1][x] != '.';
                }

            }

            if (!isdigit(matrix[y][x]) || x == width - 1) {
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
    std::vector<std::vector<number>> numbers;

    int64_t result = 0;
    int width = matrix[0].size();
    int length = matrix.size();

    for (int y = 0; y < length; ++y) {
        std::vector<number> line;
        number num{};
        for (int x = 0; x < width; ++x) {
            if (isdigit(matrix[y][x])) {
                if (num.n != 0) {
                    num.n *= 10;
                } else {
                    num.beginIndex = x;
                }
                num.n += matrix[y][x] - '0';
            }

            if (!isdigit(matrix[y][x]) || x == width - 1) {
                if (num.n != 0) {
                    num.endIndex = x - 1;
                    line.push_back(num);
                    number newNumber{};
                    num = newNumber;
                }
            }
        }

        numbers.push_back(line);
    }

    for (int y = 0; y < length; ++y) {
        for (int x = 0; x < width; ++x) {
            if (matrix[y][x] == '*') {
                int gears = 0;
                int ratio = 1;
                for (number n : numbers[y - 1]) {
                    if (n.beginIndex <= x + 1 && n.endIndex >= x - 1) {
                        ++gears;
                        ratio *= n.n;
                    }
                }
                for (number n : numbers[y]) {
                    if (n.beginIndex <= x + 1 && n.endIndex >= x - 1) {
                        ++gears;
                        ratio *= n.n;
                    }
                }
                for (number n : numbers[y + 1]) {
                    if (n.beginIndex <= x + 1 && n.endIndex >= x - 1) {
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