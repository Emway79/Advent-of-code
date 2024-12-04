#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

#include "utils.hpp"


std::vector<std::string> utils::stringSplit(const std::string& string, const std::string& delimiter) {
    std::string s = string;
    std::string token;
    size_t position;
    std::vector<std::string> result;

    while((position = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, position);
        result.push_back(token);
        s.erase(0, position + delimiter.length());
    }
    result.push_back(s.substr(0, std::string::npos));

    return result;
}


std::vector<long long> utils::findPrimes(unsigned long long limit) {
    std::vector<long long> primes;
    if (limit < 2) {
        return primes;
    }
    primes.push_back(2);

    unsigned long long i = 3;
    while (i < limit) {
        for (long long prime : primes) {
            if (prime > (long long) sqrt((double) i)) {
                primes.push_back((long long) i);
                break;
            }
            if (i % prime == 0) {
                break;
            }
        }

        i += 2;
    }

    return primes;
}

std::vector<long long> utils::findPrimesAmount(unsigned long long amount) {
    std::vector<long long> primes;
    if (amount <= 0) {
        return primes;
    }
    primes.push_back(2);

    long long i = 3;
    while (primes.size() < amount) {
        for (long long prime : primes) {
            if (prime > (long long) sqrt((double) i)) {
                primes.push_back(i);
                break;
            }
            if (i % prime == 0) {
                break;
            }
        }

        i += 2;
    }

    return primes;
}

bool utils::isPalindrome(const std::string& str) {
    int begin = 0;
    int end = str.length() - 1;

    while (begin < end) {
        if (str[begin] != str[end]) {
            return false;
        }
        ++begin;
        --end;
    }

    return true;
}

std::string utils::readFile(const std::string& pathName) {
    std::ifstream file(pathName);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<std::string> utils::readFileLines(const std::string& pathName) {
    std::ifstream file(pathName);
    std::vector<std::string> result;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            result.push_back(line);
        }
        file.close();
    }

    return result;
}

void utils::stringStrip(std::string& s, const std::string& strip) {
    int amount = 0;
    int stripIndex = 0;
    for (char& c : s) {
        if (c != strip[stripIndex]) {
            break;
        }

        ++stripIndex;
        if (stripIndex == strip.length()) {
            ++amount;
            stripIndex = 0;
        }
    }
    s.erase(0, amount * strip.length());

    amount = 0;
    stripIndex = strip.length() - 1;
    for (int i = s.length() - 1; i >= 0; --i) {
        if (s[i] != strip[stripIndex]) {
            break;
        }

        --stripIndex;
        if (stripIndex < 0) {
            ++amount;
            stripIndex = strip.length() - 1;
        }
    }

    int start = s.length() - amount * strip.length();
    s.erase(start, amount * strip.length());
}
