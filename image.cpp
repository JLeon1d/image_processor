#include "image.h"

size_t Image::GetHeight() const {
    return dib_header_.height;
}

size_t Image::GetWidth() const {
    return dib_header_.width;
}

uint32_t Image::GetFileSize() const {
    return bitmap_header_.file_size;
}

uint32_t Image::GetByteRowWidth() const {
    return utils::DivideRoundingUp(dib_header_.width * sizeof(Pixel), ROW_SIZE_ROUNDUP) * ROW_SIZE_ROUNDUP;
}

PixelArray *Image::GetPixelArray() {
    return &pixel_array_;
}

void Image::SetPixelArray(PixelArray pixel_array) {
    pixel_array_ = pixel_array;
    UpdateFileSize();
}

void Image::ReadBMP(const std::string &path) {
    std::ifstream f(path, std::ifstream::in | std::ios::binary);
    if (!f) {
        throw std::runtime_error("Can not open input file : " + path);
    }

    try {
        f.read(reinterpret_cast<char *>(&bitmap_header_), sizeof(BitmapHeader));
    } catch (...) {
        throw std::runtime_error("Failed to read bitmap header from input file : " + path);
    }

    if (bitmap_header_.signature != BMP_SIGNATURE) {
        throw std::invalid_argument("Wrong bmp signature in : " + path);
    }

    try {
        f.read(reinterpret_cast<char *>(&dib_header_), sizeof(DIBHeader));
    } catch (...) {
        throw std::runtime_error("Failed to read DIB Header from input file : " + path);
    }

    if (dib_header_.size != BMP_DIB_HEADER_SIZE) {
        throw std::invalid_argument("Wrong DIB Header size in : " + path);
    }
    if (dib_header_.color_planes != BMP_COLOR_PLANES) {
        throw std::invalid_argument("Wrong color planes in : " + path);
    }
    if (dib_header_.bits_per_pixel != BMP_BITS_FOR_PIXEL) {
        throw std::invalid_argument("Wrong bits per pixel in : " + path);
    }
    if (dib_header_.compression_method != BMP_COMPRESSION_METHOD) {
        throw std::invalid_argument("This bmp file is compressed(not supported) : " + path);
    }

    uint32_t row_size = GetByteRowWidth();
    std::vector<char> bytes(dib_header_.height * row_size);
    try {
        f.read(reinterpret_cast<char *>(bytes.data()), dib_header_.height * row_size);
    } catch (...) {
        throw std::runtime_error("Could not read pixels from : " + path);
    }

    pixel_array_.SetValueFromByteArray(bytes, dib_header_.height, dib_header_.width);
}

void Image::WriteBMP(const std::string &path) {
    std::ofstream f(path, std::ofstream::out | std::ios::binary);
    if (!f) {
        throw std::runtime_error("Can not open output file : " + path);
    }

    try {
        f.write(reinterpret_cast<char *>(&bitmap_header_), sizeof(BitmapHeader));
    } catch (...) {
        throw std::runtime_error("Could not write in file : " + path);
    }

    try {
        f.write(reinterpret_cast<char *>(&dib_header_), sizeof(DIBHeader));
    } catch (...) {
        throw std::runtime_error("Could not write in file : " + path);
    }

    auto byte_array = pixel_array_.GetByteArray();
    try {
        f.write(reinterpret_cast<char *>(byte_array.data()), static_cast<std::streamsize>(byte_array.size()));
    } catch (...) {
        throw std::runtime_error("Could not write in file : " + path);
    }
}

void Image::UpdateFileSize() {
    dib_header_.height = pixel_array_.GetHeight();
    dib_header_.width = pixel_array_.GetWidth();
    dib_header_.image_size = dib_header_.height * GetByteRowWidth();
    bitmap_header_.file_size = sizeof(BitmapHeader) + sizeof(DIBHeader) + dib_header_.image_size;
}
