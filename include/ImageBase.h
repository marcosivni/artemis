#ifndef IMAGEBASE_HPP
#define IMAGEBASE_HPP

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cmath>

//Artemis includes
#include <Pixel.h>


class Image {

    public:
        enum ImageBaseType{DICOM, JPG, PNG, BMP, KRL, NONE};

    private:
        std::string filename;
        uint32_t width; 
        uint32_t height; 
        uint16_t nchannels;
        uint32_t imageID;
        uint16_t w_Center, w_Width;
        Pixel **pixel;
        uint16_t bitsPerPixel;
        ImageBaseType imgType;
        bool photometric, wPixels;

    public:
        Image();
        Image(const Image & i);
        virtual ~Image();

        void setFilename(std::string filename);
        void setImageID(uint32_t imageID);
        void setChannels(uint16_t nchannels);
        void setPixel(uint32_t x, uint32_t y, const Pixel & pixel) throw (std::length_error, std::runtime_error);
        void setBitsPerPixel(uint16_t bitsPerPixel);
        void setWidth(uint32_t width);
        void setHeight(uint32_t height);
        void setPhotometric(bool photometric);
        void setWindowedPixels(bool wPixels);

        uint32_t getSize() const;
        std::string getFilename() const;
        uint32_t getWidth() const;
        uint32_t getHeight() const;
        uint32_t getImageID() const;
        uint16_t getChannels() const;
        uint16_t getWindowCenter() const;
        uint16_t getWindowWidth() const;
        const Pixel & getPixel(uint32_t x, uint32_t y) const throw (std::length_error, std::runtime_error);
        uint16_t getBitsPerPixel() const;

        void createPixelMatrix(uint32_t width, uint32_t height);
        void deletePixelMatrix();
        void toGrayScale();

        Image* windowing(int width, int center);

        Image * clone() const;
        bool isEqual(const Image & i) const;
        bool isPhotometric() const;
        bool windowedPixels() const;
        Image::ImageBaseType type() const;

    protected:
        void setWindowCenter(const uint16_t &w_Center);
        void setWindowWidth(const uint16_t &w_Width);
        void setType(const Image::ImageBaseType &imgType);
};

#endif

