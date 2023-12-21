#include <unordered_map>
#include <queue>
#include <numeric>

#include "Day.hpp"
#include "../Libraries/utils.hpp"


struct Module {
    std::string name;
    bool pulse;

    std::vector<std::string> inputs;
    std::vector<std::string> outputs;

    bool operator==(const Module& o) const {
        return this->name == o.name;
    }
};

namespace std {

template<>
struct hash<Module> {
    size_t operator()(const Module& m) const {
        return std::hash<std::string>{}(m.name);
    }
};

} // namespace std

namespace AOC2023 {

std::unordered_map<std::string, Module> createModules(const std::vector<std::string>& lines) {
    std::unordered_map<std::string, Module> modules;

    for (const std::string& line : lines) {
        std::vector<std::string> split = utils::stringSplit(line, " -> ");
        Module module{};
        switch(split[0][0]) {
            case '&': {
                module.name = split[0].substr(1);
                module.pulse = true;
                break;
            }
            case '%': {
                module.name = split[0].substr(1);
                module.pulse = false;
                break;
            }
            default: {
                module.name = split[0];
                module.pulse = false;
                break;
            }
        }

        std::vector<std::string> outputs;
        for (const std::string& name : utils::stringSplit(split[1], ", ")) {
            outputs.push_back(name);
        }
        module.outputs = outputs;

        modules.insert({module.name, module});
    }

    for (auto& pair : modules) {
        Module& module = pair.second;
        for (std::string& name : module.outputs) {
            if (!modules.contains(name)) {
                continue;
            }
            Module& output = modules.at(name);
            if (output.pulse) {
                output.inputs.push_back(module.name);
            }
        }
    }

    return modules;
}

int64_t solveDay20Part1() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day20.txt");
    std::unordered_map<std::string, Module> modules = createModules(lines);
    int64_t lowPulses = 0;
    int64_t highPulses = 0;

    for (int i = 0; i < 1000; ++i) {
        ++lowPulses;
        std::queue<std::string> queue;
        queue.push("broadcaster");

        while (!queue.empty()) {
            std::string curName = queue.front();
            queue.pop();
            Module& current = modules.at(curName);

            for (std::string& name : current.outputs) {
                if (current.pulse) {
                    ++highPulses;
                } else {
                    ++lowPulses;
                }

                if (!modules.contains(name)) {
                    continue;
                }

                Module& child = modules.at(name);
                if (child.inputs.empty()) {
                    if (!current.pulse) {
                        child.pulse = !child.pulse;
                        queue.push(name);
                    }
                } else {
                    queue.push(name);
                    bool pulse = true;
                    for (std::string& input : child.inputs) {
                        pulse = pulse && modules.at(input).pulse;
                    }
                    child.pulse = !pulse;
                }
            }
        }
    }

    return lowPulses * highPulses;
}

int64_t solveDay20Part2() {
    std::vector<std::string> lines = utils::readFileLines("..\\Resources\\day20.txt");
    std::unordered_map<std::string, Module> modules = createModules(lines);
    std::vector<int64_t> lows(4, 0);
    int found = 0;

    int64_t buttonPresses = 1;
    while (true) {
        std::queue<std::string> queue;
        queue.push("broadcaster");

        while (!queue.empty()) {
            std::string curName = queue.front();
            queue.pop();
            Module& current = modules.at(curName);

            // TODO REMOVE HARDCODING
            if (current.pulse) {
                if (current.name == "zc" && lows[0] == 0) {
                    lows[0] = buttonPresses;
                    ++found;
                } else if (current.name == "xt" && lows[1] == 0) {
                    lows[1] = buttonPresses;
                    ++found;
                } else if (current.name == "mk" && lows[2] == 0) {
                    lows[2] = buttonPresses;
                    ++found;
                } else if (current.name == "fp" && lows[3] == 0) {
                    lows[3] = buttonPresses;
                    ++found;
                }

                if (found == 4) {
                    goto end;
                }
            }

            for (std::string& name : current.outputs) {
                if (!modules.contains(name)) {
                    continue;
                }

                Module& child = modules.at(name);
                if (child.inputs.empty()) {
                    if (!current.pulse) {
                        child.pulse = !child.pulse;
                        queue.push(name);
                    }
                } else {
                    queue.push(name);
                    bool pulse = true;
                    for (std::string& input : child.inputs) {
                        pulse = pulse && modules.at(input).pulse;
                    }
                    child.pulse = !pulse;
                }
            }
        }

        ++buttonPresses;
    }
    end:

    int64_t result = lows[0];
    for (int i = 1; i < lows.size(); ++i) {
        result = std::lcm(result, lows[i]);
    }

    return result;
}

}