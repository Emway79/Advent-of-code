#include <unordered_map>
#include <numeric>

#include "Day.hpp"
#include "../Libraries/utils.hpp"


namespace AOC2023 {

int64_t solveDay8Part1() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day8.txt");
    std::unordered_map<std::string, std::vector<std::string>> network;

    for (int i = 2; i < lines.size(); ++i) {
        std::vector<std::string> parts = utils::stringSplit(lines[i], " = ");
        std::vector<std::string> directions = {parts[1].substr(1, 3), parts[1].substr(6, 3)};
        network.insert({parts[0], directions});
    }

    std::string current = "AAA";
    int dirIndex = 0;
    int64_t step = 0;
    while (current != "ZZZ") {
        if (dirIndex >= lines[0].size()) {
            dirIndex = 0;
        }

        if (lines[0][dirIndex] == 'L') {
            current = network[current][0];
        } else {
            current = network[current][1];
        }

        ++dirIndex;
        ++step;
    }

    return step;
}

int64_t solveDay8Part2() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day8.txt");
    std::unordered_map<std::string, std::vector<std::string>> network;
    std::vector<std::string> start;

    for (int i = 2; i < lines.size(); ++i) {
        std::vector<std::string> parts = utils::stringSplit(lines[i], " = ");
        if (parts[0][2] == 'A') {
            start.push_back(parts[0]);
        }
        std::vector<std::string> directions = {parts[1].substr(1, 3), parts[1].substr(6, 3)};
        network.insert({parts[0], directions});
    }

    std::vector<int64_t> steps;
    for (std::string& current : start) {
        int dirIndex = 0;
        int64_t step = 0;
        while (current[2] != 'Z') {
            if (dirIndex >= lines[0].size()) {
                dirIndex = 0;
            }

            if (lines[0][dirIndex] == 'L') {
                current = network[current][0];
            } else {
                current = network[current][1];
            }

            ++dirIndex;
            ++step;
        }
        steps.push_back(step);
    }

    int64_t result = steps[0];

    for (int i = 1; i < steps.size(); ++i) {
        result = std::lcm(result, steps[i]);
    }

    return result;
}

}