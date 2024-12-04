#include <unordered_set>
#include "Day.hpp"
#include "../Libraries/utils.hpp"


namespace AOC2023 {

#ifndef LONG_LONG_MAX
     #define LONG_LONG_MAX 0x7fffffffffffffffLL
#endif


int64_t solveDay5Part1() {
    std::vector<std::string> lines = utils::readFileLines("..\\src\\Resources\\day5.txt");
    std::vector<int64_t> seeds;
    for (const std::string& s : utils::stringSplit(lines[0].substr(7), " ")) {
        seeds.push_back(stoll(s));
    }

    std::vector<int> changed(seeds.size(), 0);
    for (std::string line : lines) {
        if (line.empty() || !isdigit(line[0])) {
            for (int& i : changed) {
                i = 0;
            }
            continue;
        }

        std::vector<int64_t> transform;
        for (const std::string& s : utils::stringSplit(line, " ")) {
            transform.push_back(stoll(s));
        }
        for (size_t i = 0; i < seeds.size(); ++i) {
            if (seeds[i] >= transform[1] && seeds[i] < transform[1] + transform[2] && changed[i] == 0) {
                changed[i] = 1;
                seeds[i] += (transform[0] - transform[1]);
            }
        }
    }

    int64_t result = LONG_LONG_MAX;
    for (long long seed : seeds) {
        result = std::min(result, seed);
    }

    return result;
}

int64_t solveDay5Part2() {
    std::vector<std::string> lines = utils::readFileLines("..\\src\\Resources\\day5.txt");
    std::vector<int64_t> seeds;
    for (const std::string& s : utils::stringSplit(lines[0].substr(7), " ")) {
        seeds.push_back(stoll(s));
    }

    std::vector<int> changed(seeds.size(), 0);
    for (std::string line : lines) {
        if (line.empty() || !isdigit(line[0])) {
            for (int & i : changed) {
                i = 0;
            }
            continue;
        }

        std::vector<int64_t> transform;
        for (const std::string& s : utils::stringSplit(line, " ")) {
            transform.push_back(stoll(s));
        }

        int size = seeds.size();
        for (int i = 0; i < size; i += 2) {
            int64_t start = seeds[i];
            int64_t end = seeds[i] + seeds[i + 1];
            int64_t destination = transform[0];
            int64_t source = transform[1];
            int64_t range = transform[2];
            if (changed[i] == 1 || start >= source + range || end <= source) {
                continue;
            }

            if (start < source) {
                int64_t diff = source - start;
                seeds[i] = source;
                seeds[i + 1] -= diff;
                seeds.push_back(start);
                seeds.push_back(diff);
                changed.push_back(0);
                changed.push_back(0);
                size += 2;
            }

            if (end > source + range) {
                int64_t diff = end - (source + range);
                seeds[i + 1] -= diff;
                seeds.push_back(end - diff);
                seeds.push_back(diff);
                changed.push_back(0);
                changed.push_back(0);
                size += 2;
            }

            changed[i] = 1;
            seeds[i] += (destination - source);
        }
    }

    int64_t result = LONG_LONG_MAX;
    for (int i = 0; i < seeds.size(); i += 2) {
        result = std::min(result, seeds[i]);
    }

    return result;
}

}