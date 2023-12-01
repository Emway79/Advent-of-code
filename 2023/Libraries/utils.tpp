#include <cmath>
#include <vector>
#include <stdexcept>

template <std::integral integral>
std::vector<integral> utils::getDivisors(integral number) {
    std::vector<integral> result;
    result.push_back(1);
    if (number == 1) {
        return result;
    }
    result.push_back(number);
    integral pivot = std::sqrt(number);


    for (integral i = 2; i < pivot; ++i) {
        if (number % i == 0) {
            result.push_back(i);
            result.push_back(number / i);
        }
    }

    if (number % pivot == 0 && pivot != 1) {
        if (number / pivot != pivot) {
            result.push_back(number / pivot);
        }
        result.push_back(pivot);
    }

    return result;
}

template <std::integral integral>
integral utils::sumVector(std::vector<integral> list) {
    integral result = 0;
    for (integral n : list) {
        result += n;
    }

    return result;
}

template <std::integral integral>
bool utils::isPrime(integral number) {
    if (number < 2) {
        return false;
    }

    if (number == 2 ||
        number == 3 ||
        number == 5 ||
        number == 7) {
        return true;
    }

    if (number % 2 == 0 ||
        number % 3 == 0 ||
        number % 5 == 0 ||
        number % 7 == 0) {
        return false;
    }

    integral root = (integral) ((double) sqrt(number));
    for (integral i = 11; i <= root; i += 2) {
        if (number % i == 0) {
            return false;
        }
    }

    return true;
}

// TODO negative numbers are not supported
template<std::integral integral>
std::vector<integral> utils::numToDigits(integral number) {
    int size;
    if (number < 10) {
        size = 1;
    } else if (number < 100) {
        size = 2;
    } else if (number < 1000) {
        size = 3;
    } else if (number < 10000) {
        size = 4;
    } else if (number < 100000) {
        size = 5;
    } else if (number < 1000000) {
        size = 6;
    } else if (number < 10000000) {
        size = 7;
    } else if (number < 100000000) {
        size = 8;
    } else {
        size = 9;
    }

    std::vector<integral> result(size);
    for (int i = size - 1; i >= 0; --i) {
        result[i] = number % 10;
        number /= 10;
    }

    return result;
}

template<std::integral integral>
integral utils::digitsToNum(std::vector<integral> digits) {
    integral result = 0;
    for (int i = 0; i < digits.size() - 1; ++i) {
        result += digits[i];
        result *= 10;
    }

    return result + digits[digits.size() - 1];
}

template<std::integral integral>
integral utils::factorial(integral number) {
    if (number < 0) {
        throw std::domain_error("Factorial of a number under 0 does not exist");
    }
    if (number == 0) {
        return 1;
    }

    long result = 1;
    for (int i = 2; i <= number; ++i) {
        result *= i;
    }

    return result;
}

template<std::integral integral>
std::string utils::decimalToBinary(integral number) {
    std::string result;
    while (number != 0) {
        integral remainder = number % 2;
        number /= 2;
        result += remainder;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

template<std::integral integral>
bool utils::isPalindrome(integral number) {
    integral normal = number;
    integral reverse = 0;

    while (normal > 0) {
        reverse = reverse * 10 + normal % 10;
        normal /= 10;
    }

    return number == reverse;
}
