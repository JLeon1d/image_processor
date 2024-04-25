#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include "pixel_array.h"
#include "utils.h"

const uint16_t BMP_SIGNATURE = 19778;  // BM
const uint32_t BMP_DIB_HEADER_SIZE = 40;
const uint16_t BMP_COLOR_PLANES = 1;
const uint16_t BMP_BITS_FOR_PIXEL = 24;
const uint32_t BMP_COMPRESSION_METHOD = 0;  // No compression

#pragma pack(push, 1)

struct BitmapHeader {
    uint16_t signature;  // BM
    uint32_t file_size;
    uint16_t reserved_1;
    uint16_t reserved_2;
    uint32_t offset;
};

struct DIBHeader {
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t color_planes;
    uint16_t bits_per_pixel;
    uint32_t compression_method;
    uint32_t image_size;
    uint32_t horizontal_resolution;
    uint32_t vertical_resolution;
    uint32_t colors;
    uint32_t important_colors;
};

#pragma pack(pop)

class Image {
public:
    Image() = default;

    size_t GetHeight() const;

    size_t GetWidth() const;

    uint32_t GetFileSize() const;

    uint32_t GetByteRowWidth() const;

    PixelArray* GetPixelArray();

    void SetPixelArray(PixelArray pixel_array);

    void ReadBMP(const std::string& path);

    void WriteBMP(const std::string& path);

private:
    BitmapHeader bitmap_header_;
    DIBHeader dib_header_;
    PixelArray pixel_array_;

    void UpdateFileSize();
};

#endif  // IMAGE_H
