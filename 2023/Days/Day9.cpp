#include <unordered_map>
#include <numeric>

#include "Day.hpp"
#include "../Libraries/utils.hpp"


namespace AOC2023 {


bool isAllZero(std::vector<int64_t>& numbers) {
    for (int64_t n : numbers) {
        if (n != 0) {
            return false;
        }
    }

    return true;
}


int64_t solveDay9Part1() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day9.txt");
    int64_t result = 0;

    for (std::string& line : lines) {
        std::vector<std::vector<int64_t>> data;
        std::vector<int64_t> current;
        for (std::string& s : utils::stringSplit(line, " ")) {
            current.push_back(stoll(s));
        }

        int prev = 0;
        while (!isAllZero(current)) {
            data.push_back(current);
            current = std::vector<int64_t>();
            for (auto i = 1; i < data[prev].size(); ++i) {
                current.push_back(data[prev][i] - data[prev][i - 1]);
            }
            ++prev;
        }
        current.push_back(0);
        data.push_back(current);

        for (auto i = prev - 1; i >= 0; --i) {
            std::vector<int64_t>& next = data[i];
            std::vector<int64_t>& previous = data[i + 1];

            next.push_back(next[next.size() - 1] + previous[previous.size() - 1]);
        }

        result += data[0][data[0].size() - 1];
    }

    return result;
}

int64_t solveDay9Part2() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day9.txt");
    int64_t result = 0;

    for (std::string& line : lines) {
        std::vector<std::vector<int64_t>> data;
        std::vector<int64_t> current;
        for (std::string& s : utils::stringSplit(line, " ")) {
            current.push_back(stoll(s));
        }
        std::reverse(current.begin(), current.end());

        int prev = 0;
        while (!isAllZero(current)) {
            data.push_back(current);
            current = std::vector<int64_t>();
            for (auto i = 1; i < data[prev].size(); ++i) {
                current.push_back(data[prev][i] - data[prev][i - 1]);
            }
            ++prev;
        }
        current.push_back(0);
        data.push_back(current);

        for (auto i = prev - 1; i >= 0; --i) {
            std::vector<int64_t>& next = data[i];
            std::vector<int64_t>& previous = data[i + 1];

            next.push_back(next[next.size() - 1] + previous[previous.size() - 1]);
        }

        result += data[0][data[0].size() - 1];
    }

    return result;
}

}