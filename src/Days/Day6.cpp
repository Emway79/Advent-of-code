#include <unordered_set>
#include "Day.hpp"
#include "../Libraries/utils.hpp"


namespace AOC2023 {

std::vector<int64_t> parseInt(const std::string& line) {
    std::vector<int64_t> result;
    for (const std::string& s : utils::stringSplit(line.substr(11), " ")) {
        if (!s.empty()) {
            result.push_back(stoll(s));
        }
    }

    return result;
}

std::vector<std::string> parse(const std::string& line) {
    std::vector<std::string> result;
    for (const std::string& s : utils::stringSplit(line.substr(11), " ")) {
        if (!s.empty()) {
            result.push_back(s);
        }
    }

    return result;
}


int64_t solveDay6Part1() {
    std::vector<std::string> lines = utils::readFileLines("..\\src\\Resources\\day6.txt");
    std::vector<int64_t> times = parseInt(lines[0]);
    std::vector<int64_t> distances = parseInt(lines[1]);
    int64_t result = 1;

    for (int i = 0; i < times.size(); ++i) {
        int64_t wins = 0;
        for (int64_t press = 1; press < times[i]; ++press) {
            int64_t distance = (times[i] - press) * press;
            if (distances[i] < distance) {
                ++wins;
            }
        }
        result *= wins;
    }

    return result;
}

int64_t solveDay6Part2() {
    std::vector<std::string> lines = utils::readFileLines("..\\src\\Resources\\day6.txt");
    std::vector<std::string> times = parse(lines[0]);
    std::vector<std::string> distances = parse(lines[1]);

    int64_t distance = 0;
    int64_t time = 0;
    for (int i = 0; i < times.size(); ++i) {
        time *= pow(10, times[i].size());
        time += stoll(times[i]);

        distance *= pow(10, distances[i].size());
        distance += stoll(distances[i]);
    }

    // TODO speed up with binary search or something
    int64_t result = 0;
    for (int64_t press = 1; press < time; ++press) {
        int64_t d = (time - press) * press;
        if (distance < d) {
            ++result;
        }
    }

    return result;
}

}