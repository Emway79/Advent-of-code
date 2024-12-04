#include "Day.hpp"
#include "../Libraries/utils.hpp"

namespace AOC2023 {

std::vector<int> getBrokenSprings(const std::string& s) {
    std::vector<std::string> nums = utils::stringSplit(s, ",");
    std::vector<int> result;
    for (const std::string &n : nums) {
        result.push_back(stoi(n));
    }

    return result;
}

std::vector<int> expandAmounts(const std::vector<int>& amounts) {
    std::vector<int> result;
    result.push_back(0);
    for (int amount : amounts) {
        for (int j = 0; j < amount; ++j) {
            result.push_back(1);
        }
        result.push_back(0);
    }

    return result;
}

int64_t countPossibilities(std::string& springs, std::vector<int>& amounts) {
    utils::stringStrip(springs, ".");
    springs = '.' + springs + '.';
    amounts = expandAmounts(amounts);

    std::vector<std::vector<int64_t>> mem(springs.length() + 1, std::vector<int64_t>(amounts.size() + 1, 0));
    mem[springs.length()][amounts.size()] = 1;

    for (int i = springs.length() - 1; i >= 0; i--) {
        for (int j = amounts.size() - 1; j >= 0; j--) {
            bool broken = true;
            bool operational = true;
            if (springs[i] == '#') {
                operational = false;
            } else if (springs[i] == '.') {
                broken = false;
            }

            if (broken && amounts[j]) {
                mem[i][j] += mem[i + 1][j + 1];
            } else if (operational && !amounts[j]) {
                mem[i][j] += mem[i + 1][j + 1] + mem[i + 1][j];
            }
        }
    }

    return mem[0][0];
}

void unfold(std::string& string, std::string& amounts) {
    std::string stringCopy = string;
    std::string amountsCopy = amounts;
    for (int i = 0; i < 4; ++i) {
        string += '?' + stringCopy;
        amounts += ',' + amountsCopy;
    }
}

int64_t solveDay12Part1() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day12.txt");
    int64_t result = 0;

    for (std::string& s : lines) {
        std::vector<std::string> springs = utils::stringSplit(s, " ");
        std::vector<int> amounts = getBrokenSprings(springs[1]);
        result += countPossibilities(springs[0], amounts);
    }

    return result;
}

int64_t solveDay12Part2() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day12.txt");
    int64_t result = 0;

    for (std::string& s : lines) {
        std::vector<std::string> springs = utils::stringSplit(s, " ");
        unfold(springs[0], springs[1]);
        std::vector<int> amounts = getBrokenSprings(springs[1]);
        result += countPossibilities(springs[0], amounts);
    }

    return result;
}

}