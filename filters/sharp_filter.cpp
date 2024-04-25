#include "sharp_filter.h"

SharpFilter::SharpFilter(const std::vector<std::string>& params) : Filter(params) {
}

void SharpFilter::Apply(Image& image) {
    auto pixel_array = image.GetPixelArray();
    pixel_array->ApplyMatrix(SHARP_MATRIX);
}
