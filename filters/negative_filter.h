#ifndef CPP_HSE_NEGATIVE_FILTER_H
#define CPP_HSE_NEGATIVE_FILTER_H

#include "filter.h"

class NegativeFilter : public Filter {
public:
    void Apply(Image& image) override;

    void ApplyToPixel(Pixel* pixel);

    explicit NegativeFilter(const std::vector<std::string>& params);

private:
};

#endif  // CPP_HSE_NEGATIVE_FILTER_H
