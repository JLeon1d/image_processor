#ifndef CROP_FILTER_H
#define CROP_FILTER_H

#include "filter.h"

class CropFilter : public Filter {
public:
    explicit CropFilter(const std::vector<std::string>& params);

    void Apply(Image& image) override;

private:
};

#endif  // CROP_FILTER_H
