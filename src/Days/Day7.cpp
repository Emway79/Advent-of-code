#include <algorithm>
#include "Day.hpp"
#include "../Libraries/utils.hpp"


namespace AOC2023 {

struct Hand {
    std::string cards;
    int64_t bet;
    int64_t strength;
};

bool sortHands(const Hand& left, const Hand& right) {
    if (left.strength != right.strength) {
        return left.strength < right.strength;
    }
    
    for (uint8_t i = 0; i < 5; ++i) {
        if (left.cards[i] != right.cards[i]) {
            return left.cards[i] < right.cards[i];
        }
    }
    return false;
}

int64_t getStrength(const std::string& hand, bool part2) {
    std::vector<int> amounts(15, 0);
    int jokers = 0;
    for (char c : hand) {
        if (part2 && c == '1') {
            ++jokers;
            for (int& i : amounts) {
                ++i;
            }
        } else {
            ++amounts[c - '0'];
        }
    }

    int highestAmount = 0;
    int secondHighestAmount = 0;
    for (int n : amounts) {
        if (n > highestAmount) {
            secondHighestAmount = highestAmount;
            highestAmount = n;
        } else if (n > secondHighestAmount){
            secondHighestAmount = n;
        }
    }

    if (part2) {
        secondHighestAmount -= jokers;
    }

    switch (highestAmount) {
        case 5: return 6;
        case 4: return 5;
        case 3: return 2 + secondHighestAmount;
        case 2: return secondHighestAmount;
        default: return 0;
    }
}


int64_t solveDay7Part1() {
    std::vector<std::string> lines = utils::readFileLines("..\\src\\Resources\\day7.txt");
    std::vector<Hand> hands;
    for (std::string& line : lines) {
        std::vector<std::string> split = utils::stringSplit(line, " ");
        for (char & i : split[0]) {
            switch (i) {
                case 'T': i = '9' + 1; break;
                case 'J': i = '9' + 2; break;
                case 'Q': i = '9' + 3; break;
                case 'K': i = '9' + 4; break;
                case 'A': i = '9' + 5; break;
                default: break;
            }
        }
        hands.push_back(
            Hand{
                split[0], stoll(split[1]), getStrength(split[0], false)
            }
        );
    }

    sort(hands.begin(), hands.end(), sortHands);
    int64_t result = 0;
    for (int64_t i = 1; i <= hands.size(); ++i) {
        result += i * hands[i - 1].bet;
    }

    return result;
}

int64_t solveDay7Part2() {
    std::vector<std::string> lines = utils::readFileLines("..\\src\\Resources\\day7.txt");
    std::vector<Hand> hands;
    for (std::string& line : lines) {
        std::vector<std::string> split = utils::stringSplit(line, " ");
        for (char & i : split[0]) {
            switch (i) {
                case 'T': i = '9' + 1; break;
                case 'J': i = '1'; break;
                case 'Q': i = '9' + 3; break;
                case 'K': i = '9' + 4; break;
                case 'A': i = '9' + 5; break;
                default: break;
            }
        }
        hands.push_back(
            Hand{
                split[0], stoll(split[1]), getStrength(split[0], true)
            }
        );
    }

    std::sort(hands.begin(), hands.end(), sortHands);
    int64_t result = 0;
    for (int64_t i = 1; i <= hands.size(); ++i) {
        result += i * hands[i - 1].bet;
    }

    return result;
}

}