#include <unordered_map>
#include <array>

#include "Day.hpp"
#include "../Libraries/utils.hpp"

struct Rule {
    char category;
    bool smallerThan;
    int64_t compareValue;
    std::string next;
};

namespace AOC2023 {

Rule parseRule(const std::string& s) {
    std::vector<std::string> split = utils::stringSplit(s, ":");
    if (split.size() == 1) {
        return {'0', true, 0, s};
    }
    return {s[0], s[1] == '<', stoll(split[0].substr(2)), split[1]};
}

std::vector<Rule> parseWorkflow(const std::string& input) {
    std::vector<std::string> rulesString = utils::stringSplit(input, ",");
    std::vector<Rule> rules;
    for (const std::string& rule : rulesString) {
        rules.push_back(parseRule(rule));
    }

    return rules;
}

std::array<int64_t, 4> parsePart(const std::string &input) {
    std::array<int64_t, 4> part{};
    std::vector<std::string> categories = utils::stringSplit(input.substr(1, input.size() - 2), ",");
    for (int i = 0; i < 4; ++i) {
        part[i] = stoll(categories[i].substr(2));
    }

    return part;
}

std::string getFinalWorkflow(const std::array<int64_t, 4>& part, const std::unordered_map<std::string, std::vector<Rule>>& workflows, const std::string& start) {
    if (start == "A" || start == "R") {
        return start;
    }

    const std::vector<Rule>& rules = workflows.at(start);
    for (const Rule& rule : rules) {
        int category;
        switch (rule.category) {
            case 'x': category = 0; break;
            case 'm': category = 1; break;
            case 'a': category = 2; break;
            case 's': category = 3; break;
            default: return getFinalWorkflow(part, workflows, rule.next);;
        }

        if (rule.smallerThan) {
            if (part[category] < rule.compareValue) {
                return getFinalWorkflow(part, workflows, rule.next);
            }
        } else {
            if (part[category] > rule.compareValue) {
                return getFinalWorkflow(part, workflows, rule.next);
            }
        }
    }

    return "A";
}

std::array<std::array<int64_t, 8>, 2> splitRanges(const std::array<int64_t, 8>& ranges, int64_t value, int category, bool smallerThan) {
    std::array<int64_t, 8> low = ranges;
    std::array<int64_t, 8> high = ranges;

    if (smallerThan) {
        low[category + 1] = value;
        high[category] = value;
    } else {
        low[category + 1] = value + 1;
        high[category] = value + 1;
    }

    return std::array<std::array<int64_t, 8>, 2>{low, high};
}

int64_t getAcceptedParts(std::array<int64_t, 8>& categories, const std::unordered_map<std::string, std::vector<Rule>>& workflows, const std::string& start) {
    if (start == "A") {
        return (categories[1] - categories[0]) *
               (categories[3] - categories[2]) *
               (categories[5] - categories[4]) *
               (categories[7] - categories[6]);

    } else if (start == "R") {
        return 0;
    }

    int64_t result = 0;
    const std::vector<Rule>& rules = workflows.at(start);
    for (const Rule& rule : rules) {
        int category;
        switch (rule.category) {
            case 'x': category = 0; break;
            case 'm': category = 2; break;
            case 'a': category = 4; break;
            case 's': category = 6; break;
            default: result += getAcceptedParts(categories, workflows, rule.next);;
        }

        if (rule.smallerThan) {
            if (rule.compareValue >= categories[category] && rule.compareValue < categories[category + 1]) {
                std::array<std::array<int64_t, 8>, 2> ranges = splitRanges(categories, rule.compareValue, category, true);
                categories = ranges[1];
                result += getAcceptedParts(ranges[0], workflows, rule.next);
            }
        } else {
            if (rule.compareValue >= categories[category] && rule.compareValue < categories[category + 1]) {
                std::array<std::array<int64_t, 8>, 2> ranges = splitRanges(categories, rule.compareValue, category, false);
                categories = ranges[0];
                result += getAcceptedParts(ranges[1], workflows, rule.next);
            }
        }
    }

    return result;
}


int64_t solveDay19Part1() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day19.txt");
    std::unordered_map<std::string, std::vector<Rule>> workflows;
    int64_t result = 0;

    bool readMaterials = false;
    for (const std::string& line : lines) {
        if (line.empty()) {
            readMaterials = true;
            continue;
        }

        if (!readMaterials) {
            int i = 0;
            while (line[i] != '{') {
                ++i;
            }
            workflows.insert({line.substr(0, i), parseWorkflow(line.substr(i + 1, line.size() - i - 2))});

        } else {
            std::array<int64_t, 4> part = parsePart(line);
            if (getFinalWorkflow(part, workflows, "in") == "A") {
                result += part[0] + part[1] + part[2] + part[3];
            }
        }
    }

    return result;
}

int64_t solveDay19Part2() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day19.txt");
    std::unordered_map<std::string, std::vector<Rule>> workflows;

    for (const std::string& line : lines) {
        if (line.empty()) {
            break;
        }

        int i = 0;
        while (line[i] != '{') {
            ++i;
        }
        workflows.insert({line.substr(0, i), parseWorkflow(line.substr(i + 1, line.size() - i - 2))});
    }

    std::array<int64_t, 8> categories = {1, 4001, 1, 4001, 1, 4001, 1, 4001};
    return getAcceptedParts(categories, workflows, "in");
}

}