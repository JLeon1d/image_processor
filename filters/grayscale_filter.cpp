#include "grayscale_filter.h"

GrayscaleFilter::GrayscaleFilter(const std::vector<std::string>& params) : Filter(params) {
}

void GrayscaleFilter::ApplyToPixel(Pixel* pixel) {
    double new_val = RED_COEF * pixel->GetRed() + GREEN_COEF * pixel->GetGreen() + BLUE_COEF * pixel->GetBlue();
    uint8_t pixel_val = std::min(static_cast<int32_t>(MAX_COLOR_VALUE), static_cast<int32_t>(new_val));
    pixel->SetAll(pixel_val, pixel_val, pixel_val);
}

void GrayscaleFilter::Apply(Image& image) {
    auto pixel_array = image.GetPixelArray();
    for (size_t row_id = 0; row_id < pixel_array->GetHeight(); ++row_id) {
        for (size_t col_id = 0; col_id < pixel_array->GetWidth(); ++col_id) {
            ApplyToPixel(pixel_array->GetPixel({row_id, col_id}));
        }
    }
}
