#ifndef CPP_HSE_UTILS_H
#define CPP_HSE_UTILS_H

#include <vector>
#include <string>

namespace utils {
std::vector<std::string> ParseIntoStrings(int arr_size, char **arr);

bool IsUIntNumber(const std::string_view &str);

bool IsFloatNumber(const std::string_view &str);

uint32_t DivideRoundingUp(uint32_t a, uint32_t b);
}  // namespace utils

#endif  // CPP_HSE_UTILS_H
