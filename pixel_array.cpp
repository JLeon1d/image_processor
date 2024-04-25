#include "pixel_array.h"
#include "utils.h"

PixelArray::PixelArray(const std::vector<std::vector<Pixel>>& pixel_matrix) {
    pixel_matrix_ = pixel_matrix;
}

PixelArray::~PixelArray() {
    pixel_matrix_.clear();
}

PixelArray& PixelArray::operator=(PixelArray pixel_array) {
    std::swap(pixel_matrix_, pixel_array.pixel_matrix_);
    return *this;
}

size_t PixelArray::GetHeight() const {
    return pixel_matrix_.size();
}

size_t PixelArray::GetWidth() const {
    if (pixel_matrix_.empty()) {
        return 0;
    }
    return pixel_matrix_[0].size();
}

size_t PixelArray::GetByteArrayWidth() const {
    return utils::DivideRoundingUp(GetWidth() * sizeof(Pixel), ROW_SIZE_ROUNDUP) * ROW_SIZE_ROUNDUP;
}

std::vector<std::vector<Pixel>> PixelArray::Get() const {
    return pixel_matrix_;
}

Pixel* PixelArray::GetPixel(PixelArray::Cords cords) {
    if (!AreValidCords(cords)) {
        throw std::invalid_argument("Wrong coordinates");
    }
    return &pixel_matrix_[cords.row_id][cords.col_id];
}

PixelArray PixelArray::GetSubArray(PixelArray::Cords left_up, PixelArray::Cords right_down) {
    if (left_up.row_id > right_down.row_id || left_up.col_id > right_down.col_id) {
        throw std::invalid_argument("Wrong coordinates");
    }

    right_down.row_id = std::min(right_down.row_id, GetHeight() - 1);
    right_down.col_id = std::min(right_down.col_id, GetWidth() - 1);

    size_t new_height = right_down.row_id - left_up.row_id + 1;
    size_t new_width = right_down.col_id - left_up.col_id + 1;
    std::vector<std::vector<Pixel>> new_matrix(new_height, std::vector<Pixel>(new_width));

    for (size_t i = 0; i < new_height; ++i) {
        for (size_t j = 0; j < new_width; ++j) {
            new_matrix[i][j] = pixel_matrix_[left_up.row_id + i][left_up.col_id + j];
        }
    }

    return PixelArray(new_matrix);
}

std::vector<char> PixelArray::GetByteArray() {
    size_t height = GetHeight();
    size_t width = GetWidth();
    size_t byte_width = GetByteArrayWidth();

    std::vector<char> bytes_array(height * byte_width, 0);

    for (size_t row_id = 0; row_id < height; ++row_id) {
        for (size_t col_id = 0; col_id < width; ++col_id) {  // order is BGR
            size_t array_blue_pos = bytes_array.size() - (row_id + 1) * byte_width + 3 * col_id;

            bytes_array[array_blue_pos] = static_cast<char>(pixel_matrix_[row_id][col_id].GetBlue());
            bytes_array[array_blue_pos + 1] = static_cast<char>(pixel_matrix_[row_id][col_id].GetGreen());
            bytes_array[array_blue_pos + 2] = static_cast<char>(pixel_matrix_[row_id][col_id].GetRed());
        }
    }

    return bytes_array;
}

void PixelArray::Set(PixelArray pixel_array) {
    pixel_matrix_ = pixel_array.Get();
}

void PixelArray::SetPixel(PixelArray::Cords cords, Pixel new_val) {
    if (!AreValidCords(cords)) {
        throw std::invalid_argument("wrong coordinates");
    }

    pixel_matrix_[cords.row_id][cords.col_id] = new_val;
}

void PixelArray::SetValueFromByteArray(const std::vector<char>& bytes_array, uint32_t height, uint32_t width) {
    uint32_t bytes_width = sizeof(Pixel) * width + (bytes_array.size() - sizeof(Pixel) * height * width) / height;
    pixel_matrix_.resize(height);
    for (size_t row_id = 0; row_id < height; ++row_id) {
        pixel_matrix_[height - row_id - 1].resize(width);
        for (size_t id = 0; id < width; ++id) {  // order is BGR
            uint8_t red = bytes_array[row_id * bytes_width + 3 * id + 2];
            uint8_t green = bytes_array[row_id * bytes_width + 3 * id + 1];
            uint8_t blue = bytes_array[row_id * bytes_width + 3 * id];

            pixel_matrix_[height - row_id - 1][id].SetAll(red, green, blue);
        }
    }
}

Pixel PixelArray::ApplyMatrixToPixel(PixelArray::Cords middle_cords, const std::vector<std::vector<int32_t>>& matrix) {
    if (!AreValidCords(middle_cords)) {
        throw std::invalid_argument("wrong coordinates");
    }

    int32_t new_red = 0;
    int32_t new_green = 0;
    int32_t new_blue = 0;

    int32_t red = pixel_matrix_[middle_cords.row_id][middle_cords.col_id].GetRed();
    int32_t green = pixel_matrix_[middle_cords.row_id][middle_cords.col_id].GetGreen();
    int32_t blue = pixel_matrix_[middle_cords.row_id][middle_cords.col_id].GetBlue();

    for (const auto& moves_row : MOVES) {
        for (auto [row_del, col_del] : moves_row) {
            int32_t row_id = static_cast<int32_t>(middle_cords.row_id) + row_del;
            int32_t col_id = static_cast<int32_t>(middle_cords.col_id) + col_del;

            if (AreValidCords(row_id, col_id)) {
                new_red += matrix[row_del + 1][col_del + 1] * pixel_matrix_[row_id][col_id].GetRed();
                new_green += matrix[row_del + 1][col_del + 1] * pixel_matrix_[row_id][col_id].GetGreen();
                new_blue += matrix[row_del + 1][col_del + 1] * pixel_matrix_[row_id][col_id].GetBlue();
            } else {
                auto pixel = GetClosestPixel(row_id, col_id);
                new_red += matrix[row_del + 1][col_del + 1] * pixel->GetRed();
                new_green += matrix[row_del + 1][col_del + 1] * pixel->GetGreen();
                new_blue += matrix[row_del + 1][col_del + 1] * pixel->GetBlue();
            }
        }
    }

    return Pixel(static_cast<uint8_t>(std::min(static_cast<int32_t>(MAX_COLOR_VALUE), std::max(0, new_red))),
                 static_cast<uint8_t>(std::min(static_cast<int32_t>(MAX_COLOR_VALUE), std::max(0, new_green))),
                 static_cast<uint8_t>(std::min(static_cast<int32_t>(MAX_COLOR_VALUE), std::max(0, new_blue))));
}

void PixelArray::ApplyMatrix(const std::vector<std::vector<int32_t>>& matrix) {
    std::vector<std::vector<Pixel>> new_pixel_matrix(GetHeight(), std::vector<Pixel>(GetWidth()));

    for (size_t row_id = 0; row_id < GetHeight(); ++row_id) {
        for (size_t col_id = 0; col_id < GetWidth(); ++col_id) {
            new_pixel_matrix[row_id][col_id] = ApplyMatrixToPixel({row_id, col_id}, matrix);
        }
    }

    pixel_matrix_ = new_pixel_matrix;
}

bool PixelArray::AreValidCords(int32_t row, int32_t col) const {
    if (row < 0 || col < 0 || row >= static_cast<int32_t>(GetHeight()) || col >= static_cast<int32_t>(GetWidth())) {
        return false;
    }
    return true;
}

bool PixelArray::AreValidCords(Cords cords) const {
    if (cords.row_id >= GetHeight() || cords.col_id >= GetWidth()) {
        return false;
    }
    return true;
}

Pixel* PixelArray::GetClosestPixel(int32_t row_id, int32_t col_id) {
    if (AreValidCords(row_id, col_id)) {
        return GetPixel({static_cast<size_t>(row_id), static_cast<size_t>(col_id)});
    }

    row_id = std::max(0, std::min(static_cast<int32_t>(GetHeight()), row_id));
    col_id = std::max(0, std::min(static_cast<int32_t>(GetWidth()), col_id));

    return GetPixel({static_cast<size_t>(row_id), static_cast<size_t>(col_id)});
}

PixelArray::Cords PixelArray::GetClosestPixelCords(int32_t row_id, int32_t col_id) {
    if (AreValidCords(row_id, col_id)) {
        return {static_cast<size_t>(row_id), static_cast<size_t>(col_id)};
    }

    row_id = std::max(0, std::min(static_cast<int32_t>(GetHeight()), row_id));
    col_id = std::max(0, std::min(static_cast<int32_t>(GetWidth()), col_id));

    return {static_cast<size_t>(row_id), static_cast<size_t>(col_id)};
}
