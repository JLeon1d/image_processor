#ifndef CPP_HSE_EDGE_DETECTION_FILTER_H
#define CPP_HSE_EDGE_DETECTION_FILTER_H

#include "filter.h"
#include "grayscale_filter.h"
#include <memory>

const std::vector<std::vector<int32_t>> EDGE_DETECTION_MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

class EdgeDetectionFilter : public Filter {
public:
    explicit EdgeDetectionFilter(const std::vector<std::string>& params);

    void Apply(Image& image) override;

private:
};

#endif  // CPP_HSE_EDGE_DETECTION_FILTER_H
