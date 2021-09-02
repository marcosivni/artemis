#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cstdlib>
#include <iostream>

class Pixel {

    private:
        uint8_t r, g, b;
        float grayPixel;

    public:
        Pixel();
        Pixel(uint8_t r, uint8_t g, uint8_t b);
        Pixel(uint8_t r, uint8_t g, uint8_t b, float grayPixel);
        Pixel(float grayValue);
        Pixel(const Pixel & pixel);
        ~Pixel();

        void setRedPixelValue(uint8_t r);
        void setGreenPixelValue(uint8_t g);
        void setBluePixelValue(uint8_t b);
        void setRGBPixelValue(uint8_t r, uint8_t g, uint8_t b);
        void setGrayPixelValue(float grayValue);

        void toGrayScale();

        float getGrayPixelValue() const;
        uint8_t getRedPixelValue() const;
        uint8_t getGreenPixelValue() const;
        uint8_t getBluePixelValue() const;

        Pixel * clone() const;
        bool isEqual(const Pixel & p) const;
};

#endif
