#ifndef CPP_HSE_GRAYSCALE_FILTER_H
#define CPP_HSE_GRAYSCALE_FILTER_H

#include "filter.h"

double const RED_COEF = 0.299;
double const GREEN_COEF = 0.587;
double const BLUE_COEF = 0.114;

class GrayscaleFilter : public Filter {
public:
    explicit GrayscaleFilter(const std::vector<std::string>& params);

    void Apply(Image& image) override;

    void ApplyToPixel(Pixel* pixel);

private:
};

#endif  // CPP_HSE_GRAYSCALE_FILTER_H
