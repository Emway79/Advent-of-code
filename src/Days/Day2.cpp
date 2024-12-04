#include "Day.hpp"
#include "../Libraries/utils.hpp"

namespace AOC2023 {

int64_t solveDay2Part1() {
    int red = 12;
    int blue = 14;
    int green = 13;
    int64_t result = 0;
    int id = 1;
    int cutoff = 8;
    std::vector<std::string> list = utils::readFileLines("..\\src\\Resources\\day2.txt");

    for (const std::string& line : list) {
        int maxRed = 0;
        int maxBlue = 0;
        int maxGreen = 0;
        std::string game = line.substr(cutoff);

        for (const std::string& pull : utils::stringSplit(game, "; ")) {
            for (const std::string& item : utils::stringSplit(pull, ", ")) {
                std::vector<std::string> color = utils::stringSplit(item, " ");
                int n = std::stoi(color[0]);

                if (color[1] == "red") {
                    maxRed = std::max(maxRed, n);
                } else if (color[1] == "green") {
                    maxGreen = std::max(maxGreen, n);
                } else {
                    maxBlue = std::max(maxBlue, n);
                }
            }
        }

        if (maxRed <= red && maxBlue <= blue && maxGreen <= green) {
            result += id;
        }
        ++id;
        if (id >= 10) {
            cutoff = 9;
        }
        if (id >= 100) {
            cutoff = 10;
        }
    }

    return result;
}

int64_t solveDay2Part2() {
    int64_t result = 0;
    int id = 1;
    int cutoff = 8;
    std::vector<std::string> list = utils::readFileLines("..\\src\\Resources\\day2.txt");

    for (const std::string& line : list) {
        int maxRed = 0;
        int maxBlue = 0;
        int maxGreen = 0;
        std::string game = line.substr(cutoff);

        for (const std::string& pull : utils::stringSplit(game, "; ")) {
            for (const std::string& item : utils::stringSplit(pull, ", ")) {
                std::vector<std::string> color = utils::stringSplit(item, " ");
                int n = std::stoi(color[0]);

                if (color[1] == "red") {
                    maxRed = std::max(maxRed, n);
                } else if (color[1] == "green") {
                    maxGreen = std::max(maxGreen, n);
                } else {
                    maxBlue = std::max(maxBlue, n);
                }
            }
        }

        result += maxRed * maxGreen * maxBlue;
        ++id;
        if (id >= 10) {
            cutoff = 9;
        }
        if (id >= 100) {
            cutoff = 10;
        }
    }

    return result;
}

}
