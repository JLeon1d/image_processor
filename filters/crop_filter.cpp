#include "crop_filter.h"

CropFilter::CropFilter(const std::vector<std::string>& params) : Filter(params) {
}

void CropFilter::Apply(Image& image) {
    size_t new_height = static_cast<size_t>(std::stoi(params_[0]));
    size_t new_width = static_cast<size_t>(std::stoi(params_[1]));
    auto pixel_array = image.GetPixelArray();
    image.SetPixelArray(pixel_array->GetSubArray({0, 0}, {new_height - 1, new_width - 1}));
}
