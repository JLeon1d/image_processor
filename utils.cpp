#include "utils.h"

namespace utils {
std::vector<std::string> ParseIntoStrings(int arr_size, char **arr) {
    std::vector<std::string> res;
    for (size_t i = 0; i < static_cast<size_t>(arr_size); ++i) {
        res.push_back(std::string(arr[i]));
    }
    return res;
}

bool IsUIntNumber(const std::string_view &str) {
    for (const char &ch : str) {
        if (!std::isdigit(ch)) {
            return false;
        }
    }
    return true;
}

bool IsFloatNumber(const std::string_view &str) {
    if (IsUIntNumber(str)) {
        return true;
    }

    int32_t dot_cnt = 0;
    for (const char &ch : str) {
        if (!std::isdigit(ch)) {
            if (ch == '.') {
                ++dot_cnt;
            } else {
                return false;
            }
        }
    }

    return dot_cnt == 1;
}

uint32_t DivideRoundingUp(uint32_t a, uint32_t b) {
    return (a + b - 1) / b;
}
}  // namespace utils
