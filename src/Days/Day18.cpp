#include "Day.hpp"
#include "../Libraries/utils.hpp"

struct Coord {
    int64_t row;
    int64_t column;
};

namespace AOC2023 {

int64_t getPerimeter(std::vector<Coord> &coords) {
    int64_t result = 0;
    for (int i = 0; i < coords.size() - 1; ++i) {
        if (coords[i].row != coords[i + 1].row) {
            result += std::abs(coords[i].row - coords[i + 1].row);
        } else {
            result += std::abs(coords[i].column - coords[i + 1].column);
        }
    }

    if (coords[0].row != coords[coords.size() - 1].row) {
        result += std::abs(coords[0].row - coords[coords.size() - 1].row);
    } else {
        result += std::abs(coords[0].column - coords[coords.size() - 1].column);
    }

    return result;
}

int64_t getArea(std::vector<Coord>& coords) {
    int64_t area = 0;
    for (int i = 0; i < coords.size() - 1; ++i) {
        area += (coords[i].row * coords[i + 1].column) - (coords[i].column * coords[i + 1].row);
    }

    area += (coords[coords.size() - 1].row * coords[0].column) - (coords[coords.size() - 1].column * coords[0].row)/ 2;
    int64_t perimeter = getPerimeter(coords);

    return (std::abs(area) + perimeter) / 2 + 1;
}

int64_t solveDay18Part1() {
    std::vector<std::string> lines = utils::readFileLines("..\\src\\Resources\\day18.txt");
    std::vector<Coord> coords;
    Coord location = {0, 0};

    for (std::string& line : lines) {
        std::vector<std::string> input = utils::stringSplit(line, " ");
        int64_t distance = std::stoll(input[1]);
        switch(input[0][0]) {
            case 'L': location.column -= distance; break;
            case 'R': location.column += distance; break;
            case 'U': location.row -= distance; break;
            case 'D': location.row += distance; break;
        }
        coords.push_back(location);
    }

    return getArea(coords);
}

int64_t solveDay18Part2() {
    std::vector<std::string> lines = utils::readFileLines("..\\src\\Resources\\day18.txt");
    std::vector<Coord> coords;
    Coord location = {0, 0};

    for (std::string& line : lines) {
        std::vector<std::string> input = utils::stringSplit(line, " ");
        std::string s = input[2].substr(2, 5);
        int64_t distance = std::stoll(s, nullptr, 16);
        switch(input[2][7]) {
            case '2': location.column -= distance; break;
            case '0': location.column += distance; break;
            case '3': location.row -= distance; break;
            case '1': location.row += distance; break;
        }
        coords.push_back(location);
    }

    return getArea(coords);
}

}