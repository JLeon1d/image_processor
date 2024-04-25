#ifndef CPP_HSE_BLUR_FILTER_H
#define CPP_HSE_BLUR_FILTER_H

#include "filter.h"
#include <valarray>

const double MAX_DELTA_COEF = 3.0;

class BlurFilter : public Filter {
public:
    explicit BlurFilter(const std::vector<std::string>& params);

    void Apply(Image& image) override;

private:
};

#endif  // CPP_HSE_BLUR_FILTER_H
