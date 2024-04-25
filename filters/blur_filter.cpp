#include "blur_filter.h"

BlurFilter::BlurFilter(const std::vector<std::string> &params) : Filter(params) {
}

void BlurFilter::Apply(Image &image) {
    size_t height = image.GetHeight();
    size_t width = image.GetWidth();

    double sigma = std::stod(params_[0]);
    if (sigma == 0.0) {
        return;
    }
    double denom = acos(-1.0) * sigma * sigma * 2;  // acos(-1) = pi
    int32_t max_delta = ceil(MAX_DELTA_COEF * sigma);

    std::vector<double> exps(max_delta + 1);  // powers of e calculating
    for (size_t del = 0; del < max_delta + 1; ++del) {
        double pow = -(static_cast<double>(static_cast<int64_t>(del) * del) / (sigma * sigma * 2));
        exps[del] = exp(pow);
    }

    auto pixel_matrix = image.GetPixelArray();

    std::vector<std::vector<double>> row_gauss_red(height, std::vector<double>(width));
    std::vector<std::vector<double>> row_gauss_green(height, std::vector<double>(width));
    std::vector<std::vector<double>> row_gauss_blue(height, std::vector<double>(width));
    for (size_t row_id = 0; row_id < height; ++row_id) {
        for (size_t col0_id = 0; col0_id < width; ++col0_id) {
            int32_t min_col_id = static_cast<int32_t>(col0_id) - max_delta;

            for (int32_t col_id = min_col_id; col_id < col0_id + max_delta + 1; ++col_id) {
                int32_t del = std::abs(static_cast<int32_t>(col0_id) - col_id);

                auto pixel = pixel_matrix->GetClosestPixel(static_cast<int32_t>(row_id), col_id);

                row_gauss_red[row_id][col0_id] += exps[del] * static_cast<double>(pixel->GetRedFloat());
                row_gauss_green[row_id][col0_id] += exps[del] * static_cast<double>(pixel->GetGreenFloat());
                row_gauss_blue[row_id][col0_id] += exps[del] * static_cast<double>(pixel->GetBlueFloat());
            }
        }
    }

    for (size_t row_id = 0; row_id < height; ++row_id) {
        for (size_t col_id = 0; col_id < width; ++col_id) {
            double new_red = 0.0;
            double new_green = 0.0;
            double new_blue = 0.0;

            int32_t min_row_id = static_cast<int32_t>(row_id) - max_delta;

            for (int32_t id = min_row_id; id < row_id + max_delta + 1; ++id) {
                int32_t del = std::abs(static_cast<int32_t>(row_id) - id);

                auto cords = pixel_matrix->GetClosestPixelCords(id, static_cast<int32_t>(col_id));

                new_red += exps[del] * row_gauss_red[cords.row_id][cords.col_id];
                new_green += exps[del] * row_gauss_green[cords.row_id][cords.col_id];
                new_blue += exps[del] * row_gauss_blue[cords.row_id][cords.col_id];
            }

            new_red /= denom;
            new_green /= denom;
            new_blue /= denom;

            pixel_matrix->GetPixel({row_id, col_id})->SetAllFloat(new_red, new_green, new_blue);
        }
    }
}
