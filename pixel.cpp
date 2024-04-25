#include "pixel.h"

Pixel::Pixel() : red_(0), green_(0), blue_(0) {
}

Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue) : red_(red), green_(green), blue_(blue) {
}

Pixel& Pixel::operator=(Pixel pixel) {
    std::swap(red_, pixel.red_);
    std::swap(green_, pixel.green_);
    std::swap(blue_, pixel.blue_);
    return *this;
}

uint8_t Pixel::GetRed() const {
    return red_;
}

uint8_t Pixel::GetGreen() const {
    return green_;
}

uint8_t Pixel::GetBlue() const {
    return blue_;
}

void Pixel::SetRed(uint8_t red) {
    red_ = red;
}

void Pixel::SetGreen(uint8_t green) {
    green_ = green;
}

void Pixel::SetBlue(uint8_t blue) {
    blue_ = blue;
}

void Pixel::SetAll(uint8_t red, uint8_t green, uint8_t blue) {
    SetRed(red);
    SetGreen(green);
    SetBlue(blue);
}

double Pixel::GetRedFloat() const {
    return static_cast<double>(red_) / static_cast<double>(MAX_COLOR_VALUE);
}

double Pixel::GetGreenFloat() const {
    return static_cast<double>(green_) / static_cast<double>(MAX_COLOR_VALUE);
}

double Pixel::GetBlueFloat() const {
    return static_cast<double>(blue_) / static_cast<double>(MAX_COLOR_VALUE);
}

void Pixel::SetRedFloat(double red) {
    red = std::round(red * MAX_COLOR_VALUE);
    red = std::max(0.0, std::min(static_cast<double>(MAX_COLOR_VALUE), red));
    red_ = static_cast<uint8_t>(red);
}

void Pixel::SetGreenFloat(double green) {
    green = std::round(green * MAX_COLOR_VALUE);
    green = std::max(0.0, std::min(static_cast<double>(MAX_COLOR_VALUE), green));
    green_ = static_cast<uint8_t>(green);
}

void Pixel::SetBlueFloat(double blue) {
    blue = std::round(blue * MAX_COLOR_VALUE);
    blue = std::max(0.0, std::min(static_cast<double>(MAX_COLOR_VALUE), blue));
    blue_ = static_cast<uint8_t>(blue);
}

void Pixel::SetAllFloat(double red, double green, double blue) {
    SetRedFloat(red);
    SetGreenFloat(green);
    SetBlueFloat(blue);
}
