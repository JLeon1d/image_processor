#ifndef CPP_HSE_SHARP_FILTER_H
#define CPP_HSE_SHARP_FILTER_H

#include "filter.h"

const std::vector<std::vector<int32_t>> SHARP_MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

class SharpFilter : public Filter {
public:
    explicit SharpFilter(const std::vector<std::string>& params);

    void Apply(Image& image) override;

private:
};

#endif  // CPP_HSE_SHARP_FILTER_H
