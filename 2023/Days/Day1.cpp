#include "../Libraries/utils.hpp"

namespace AOC2023 {

std::string num[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};


int64_t solveDay1Part1() {
    std::vector<std::string> list = utils::readFileLines("..\\Resources\\day1.txt");
    long long result = 0;
    for (std::string s: list) {
        std::vector<int> nums;
        for (char c: s) {
            if (isdigit(c)) {
                nums.push_back(c - '0');
            }
        }
        result += nums[0] * 10 + nums[nums.size() - 1];
    }

    return result;
}

int64_t solveDay1Part2() {
    std::vector<std::string> list = utils::readFileLines("..\\Resources\\day1.txt");
    long long result = 0;
    for (std::string s : list) {
        std::vector<int> nums;
        int index = 0;
        for (char c : s) {
            if (isdigit(c)) {
                nums.push_back(c - '0');
            } else  {
                std::string si = s.substr(index, s.size());
                for (int i = 0; i < 9; ++i) {
                    if (si.starts_with(num[i])) {
                        nums.push_back(i + 1);
                        break;
                    }
                }
            }
            index++;
        }
        result += nums[0] * 10 + nums[nums.size() - 1];
        ++index;
    }

    return result;
}

}