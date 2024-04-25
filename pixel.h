#ifndef PIXEL_H
#define PIXEL_H

#include <cstdint>
#include <algorithm>
#include <cmath>

const uint8_t MAX_COLOR_VALUE = UINT8_MAX;

class Pixel {
public:
    Pixel();

    Pixel(uint8_t red, uint8_t green, uint8_t blue);

    Pixel(const Pixel& pixel) = default;

    ~Pixel() = default;

    Pixel& operator=(Pixel pixel);

    uint8_t GetRed() const;

    uint8_t GetGreen() const;

    uint8_t GetBlue() const;

    double GetRedFloat() const;

    double GetGreenFloat() const;

    double GetBlueFloat() const;

    void SetRed(uint8_t red);

    void SetGreen(uint8_t green);

    void SetBlue(uint8_t blue);

    void SetAll(uint8_t red, uint8_t green, uint8_t blue);

    void SetRedFloat(double red);

    void SetGreenFloat(double green);

    void SetBlueFloat(double blue);

    void SetAllFloat(double red, double green, double blue);

private:
    uint8_t red_;
    uint8_t green_;
    uint8_t blue_;
};

#endif  // PIXEL_H
