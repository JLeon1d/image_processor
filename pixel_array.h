#ifndef PIXEL_ARRAY_H
#define PIXEL_ARRAY_H

#include "pixel.h"
#include <vector>
#include <stdexcept>

const uint32_t ROW_SIZE_ROUNDUP = 4;  // Each row's size in bytes has to be a multiple of 4;

const std::vector<std::vector<std::pair<int32_t, int32_t>>> MOVES = {
    {{-1, -1}, {-1, 0}, {-1, 1}}, {{0, -1}, {0, 0}, {0, 1}}, {{1, -1}, {1, 0}, {1, 1}}};

class PixelArray {
public:
    struct Cords {
        size_t row_id;
        size_t col_id;
    };

    PixelArray() = default;

    explicit PixelArray(const std::vector<std::vector<Pixel>>& pixel_matrix);

    PixelArray(const PixelArray& pixel_array) = default;

    ~PixelArray();

    PixelArray& operator=(PixelArray pixel_array);

    size_t GetHeight() const;

    size_t GetWidth() const;

    size_t GetByteArrayWidth() const;

    std::vector<std::vector<Pixel>> Get() const;

    Pixel* GetPixel(Cords cords);
    Pixel* GetClosestPixel(int32_t row_id, int32_t col_id);
    Cords GetClosestPixelCords(int32_t row_id, int32_t col_id);

    PixelArray GetSubArray(Cords left_up, Cords right_down);

    std::vector<char> GetByteArray();

    void Set(PixelArray pixel_array);

    void SetPixel(Cords cords, Pixel new_val);

    void SetValueFromByteArray(const std::vector<char>& bytes_array, uint32_t height, uint32_t width);

    Pixel ApplyMatrixToPixel(Cords pixel, const std::vector<std::vector<int32_t>>& matrix);

    void ApplyMatrix(const std::vector<std::vector<int32_t>>& matrix);

    bool AreValidCords(int32_t row, int32_t col) const;

    bool AreValidCords(Cords cords) const;

private:
    std::vector<std::vector<Pixel>> pixel_matrix_;
};

#endif  // PIXEL_ARRAY_H
