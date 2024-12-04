#include "Day.hpp"
#include "../Libraries/utils.hpp"

namespace AOC2023 {

struct Lens {
    std::string label;
    int strength;

    bool operator==(const Lens& other) const {
        return (this->label == other.label);
    }
};

int64_t asciiHash(const std::string& s) {
    int64_t result = 0;
    for (const char& c : s) {
        result += c;
        result *= 17;
        result %= 256;
    }

    return result;
}

int64_t asciiLabelHash(const std::string& s) {
    int64_t result = 0;
    for (const char& c : s) {
        if (c == '=' || c == '-') {
            return result;
        }
        result += c;
        result *= 17;
        result %= 256;
    }

    return result;
}


int64_t solveDay15Part1() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day15.txt");
    int64_t result = 0;
    for (std::string& s : utils::stringSplit(lines[0], ",")) {
        result += asciiHash(s);
    }

    return result;
}

int64_t solveDay15Part2() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day15.txt");
    std::vector<std::vector<Lens>> boxes(256, std::vector<Lens>());

    for (std::string& s : utils::stringSplit(lines[0], ",")) {
        std::vector<Lens>& box = boxes[asciiLabelHash(s)];
        if (s[s.size() - 2] == '=') {
            Lens lens = {s.substr(0, s.size() - 2), s[s.size() - 1] - '0'};
            auto position = std::find(box.begin(), box.end(), lens);
            if (position == box.end()) {
                box.push_back(lens);
            } else {
                *position = lens;
            }
        } else {
            Lens lens = {s.substr(0, s.size() - 1), s[s.size() - 1] - '0'};
            auto position = std::find(box.begin(), box.end(), lens);
            if (position != box.end()) {
                box.erase(position);
            }
        }
    }

    int64_t result = 0;
    for (int i = 0; i < boxes.size(); ++i) {
        std::vector<Lens>& box = boxes[i];
        for (int j = 0; j < box.size(); ++j) {
            result += (i + 1) * (j + 1) * box[j].strength;
        }
    }


    return result;
}

}