#include <unordered_set>
#include "Day.hpp"
#include "../Libraries/utils.hpp"


namespace AOC2023 {


int64_t solveDay4Part1() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day4.txt");
    int64_t result = 0;
    for (std::string& line : lines) {
        std::vector<std::string> sides = utils::stringSplit(line.substr(9), " | ");
        std::unordered_set<int64_t> win;
        for (std::string n : utils::stringSplit(sides[0], " ")) {
            if (n.empty()) {
                continue;
            }
            win.insert(std::stoll(n));
        }

        int64_t score = 0;
        for (std::string n : utils::stringSplit(sides[1], " ")) {
            if (n.empty()) {
                continue;
            }
            int64_t points = std::stoll(n);
            if (win.contains(points)) {
                if (score == 0) {
                    score = 1;
                } else {
                    score *= 2;
                }
            }
        }

        result += score;
    }

    return result;
}

int64_t solveDay4Part2() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day4.txt");
    std::vector<int64_t> copies(lines.size(), 1);
    int card = 1;

    for (std::string& line : lines) {
        std::vector<std::string> sides = utils::stringSplit(line.substr(9), " | ");
        std::unordered_set<int64_t> win;
        for (std::string n : utils::stringSplit(sides[0], " ")) {
            if (n.empty()) {
                continue;
            }
            win.insert(std::stoll(n));
        }

        int64_t amount = 0;
        for (std::string n : utils::stringSplit(sides[1], " ")) {
            if (n.empty()) {
                continue;
            }
            int64_t points = std::stoll(n);
            if (win.contains(points)) {
                ++amount;
            }
        }

        for (int i = card; i < lines.size() && i < card + amount; ++i) {
            copies[i] += copies[card - 1];
        }
        ++card;
    }

    int64_t result = 0;
    for (int64_t n : copies) {
        result += n;
    }

    return result;
}

}