#include "negative_filter.h"

NegativeFilter::NegativeFilter(const std::vector<std::string>& params) : Filter(params) {
}

void NegativeFilter::ApplyToPixel(Pixel* pixel) {
    pixel->SetAll(MAX_COLOR_VALUE - pixel->GetRed(), MAX_COLOR_VALUE - pixel->GetGreen(),
                  MAX_COLOR_VALUE - pixel->GetBlue());
}

void NegativeFilter::Apply(Image& image) {
    auto pixel_array = image.GetPixelArray();
    for (size_t row_id = 0; row_id < pixel_array->GetHeight(); ++row_id) {
        for (size_t col_id = 0; col_id < pixel_array->GetWidth(); ++col_id) {
            ApplyToPixel(pixel_array->GetPixel({row_id, col_id}));
        }
    }
}
