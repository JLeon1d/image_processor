#include "edge_detection_filter.h"

EdgeDetectionFilter::EdgeDetectionFilter(const std::vector<std::string>& params) : Filter(params) {
}

void EdgeDetectionFilter::Apply(Image& image) {
    std::unique_ptr<GrayscaleFilter> grayscale_filter = std::make_unique<GrayscaleFilter>(GrayscaleFilter({}));
    grayscale_filter->Apply(image);

    auto pixel_array = image.GetPixelArray();
    pixel_array->ApplyMatrix(EDGE_DETECTION_MATRIX);

    uint8_t threshold = static_cast<uint8_t>(std::stod(params_[0]) * MAX_COLOR_VALUE);
    for (size_t row_id = 0; row_id < pixel_array->GetHeight(); ++row_id) {
        for (size_t col_id = 0; col_id < pixel_array->GetWidth(); ++col_id) {
            auto pixel = pixel_array->GetPixel({row_id, col_id});
            if (pixel->GetRed() <= threshold) {  // all colors are equal after grayscale filter
                pixel->SetAll(0, 0, 0);
            } else {
                pixel->SetAll(MAX_COLOR_VALUE, MAX_COLOR_VALUE, MAX_COLOR_VALUE);
            }
        }
    }
}
