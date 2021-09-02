/* Copyright 2003-2017 GBDI-ICMC-USP <caetano@icmc.usp.br>
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*   http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include <ImageBase.h>


/**
* Constructor.
*/
Image::Image() {

    setWidth(0);
    setHeight(0);
    setFilename("NO_FILE");
    setImageID(0);
    setChannels(0);
    setBitsPerPixel(0);

    setType(ImageBaseType::NONE);
    setWindowCenter(0);
    setWindowWidth(0);

    pixel = NULL;
}

/**
* Clone-Constructor.
*/
Image::Image(const Image & i) {

    pixel = NULL;
    createPixelMatrix(i.getWidth(), i.getHeight());

    for (uint32_t x = 0; x < i.getWidth(); x++) {
        for (uint32_t y = 0; y < i.getHeight(); y++) {
            Pixel p(i.getPixel(x, y));
            setPixel(x, y, p);
        }
    }

    setType(i.type());
    setWindowCenter(i.getWindowCenter());
    setWindowWidth(i.getWindowWidth());

    setFilename(i.getFilename());
    setImageID(i.getImageID());
    setChannels(i.getChannels());
    setBitsPerPixel(i.getBitsPerPixel());
}

/**
* Destructor.
*/
Image::~Image() {

    deletePixelMatrix();
}

/**
* Sets a filename of the image.
*
* @param filename: A file name of the image.
*/
void Image::setFilename(std::string filename) {

    this->filename = filename;
}

/**
* Sets a image id.
*
* @param imageID: A id of the image.
*/
void Image::setImageID(uint32_t imageID) {

    this->imageID = imageID;
}

/**
* Sets a number of channels of the image.
*
* @param nchannels: The number of the channels of the image.
*/
void Image::setChannels(uint16_t nchannels) {

    this->nchannels = nchannels;
}

/**
* Sets a pixel object.
*
* @param x: The x position in the matrix of pixel.
* @param y: The y position in the matrix of pixel.
* @param pixel: The pixel object to be set.
*/
void Image::setPixel(uint32_t x, uint32_t y, const Pixel & pixel) throw (std::length_error, std::runtime_error){

    if (this->pixel != NULL) {
        if ((x >= 0) && (x < getWidth()) && (y >= 0) && (y < getHeight())) {
            /* Create a copy of pixel and store it in the pixel matrix */
            Pixel p(pixel);
            this->pixel[x][y] = p;
        } else {
            throw std::length_error("Out of bounds when setting a pixel");
        }
    } else {
        throw std::runtime_error("Matrix was empty. Cannot set a pixel.");
    }
}

/**
* Sets a bits per pixel value.
*
* @param bitsPerPixel: The number of the bits per pixel of the image.
*/
void Image::setBitsPerPixel(uint16_t bitsPerPixel) {

    this->bitsPerPixel = bitsPerPixel;
}

/**
* Sets a width of the image.
*
* @param width A width of the image.
*/
void Image::setWidth(uint32_t width){

    this->width = width;
}

/**
* Sets a height of the image.
*
* @param height A height of the image.
*/
void Image::setHeight(uint32_t height){

    this->height = height;
}

/**
* Sets a size of the image.
*
* @param size A size of the image.
*/
uint32_t Image::getSize() const {

    return (width * height);
}

/**
* Gets a image filename.
*
* @return A filename.
*/
std::string Image::getFilename() const {

    return filename;
}

/**
* Gets a image width.
*
* @return A width of the image.
*/
uint32_t Image::getWidth() const{

    return width;
}

/**
* Gets a image heigth.
*
* @return A image height.
*/
uint32_t Image::getHeight() const {

    return height;
}

/**
* Gets a image id.
*
* @return A image id.
*/
uint32_t Image::getImageID() const {

    return imageID;
}

/**
* Gets number of channels of the image.
*
* @return The number of channels of the image.
*/
uint16_t Image::getChannels() const {

    return nchannels;
}

uint16_t Image::getWindowCenter() const {

    return w_Center;
}

uint16_t Image::getWindowWidth() const {

    return w_Width;
}

/**
* Gets a pixel object of the image.
*
* @return A copy a of the pixel object.
*/
const Pixel & Image::getPixel(uint32_t x, uint32_t y) const throw (std::length_error, std::runtime_error) {

    if (this->pixel != NULL) {
        if ((x >= 0) && (x < getWidth()) && (y >= 0) && (y < getHeight()))
            return this->pixel[x][y];
        else {
            throw std::length_error("Out of bounds when getting pixel");
        }
    } else {
        throw std::runtime_error("Matrix was empty. Cannot get the pixel value");
    }
}

/**
* Gets a number of bits per pixel.
*
* @return The number of bits per pixel.
*/
uint16_t Image::getBitsPerPixel() const {

    return bitsPerPixel;
}

/**
* Creates a pixel matrix.
*
* @param width: The width of the image.
* @param height: The height of the image.
*/
void Image::createPixelMatrix(uint32_t width, uint32_t height) {

    setWidth(width);
    setHeight(height);
    deletePixelMatrix();
    //Build the pixel matrix with dynamic values
    pixel = new Pixel*[width];
    for (uint16_t i = 0; i < width; i++)
        pixel[i] = new Pixel[height];
}

/**
* Clear and free the pixel matrix.
*/
void Image::deletePixelMatrix() {

    if (pixel != NULL) {
        for (uint16_t i = 0; i < getWidth(); i++) {
            delete[] pixel[i];
        }
        delete[] pixel;
        pixel = NULL;
        setWidth(0);
        setHeight(0);
    }
}

/**
* Converts an image to gray scale.
*/
void Image::toGrayScale(){

    for (uint32_t x = 0; x < getWidth(); x++){
        for (uint32_t y = 0; y < getHeight(); y++){
            Pixel *p = new Pixel(getPixel(x, y));
            p->toGrayScale();
            setPixel(x, y, *p);
            delete(p);
        }
    }
}

/**
* Clones the image.
*
* @return A cloned image.
*/
Image * Image::clone() const {
    return new Image(*this);
}


/**
* Compares two images.
*
* @param i A image to be compared.
* @return True if the images are equal, false otherwise.
*/
bool Image::isEqual(const Image & i) const {

    if (i.getHeight() != this->getHeight()) {
        return false;
    }

    if (i.getWidth() != this->getWidth()) {
        return false;
    }

    for (uint32_t x = 0; x < i.getWidth(); x++) {
        for (uint32_t y = 0; y < i.getHeight(); y++) {
            if (!(i.getPixel(x, y).isEqual(this->getPixel(x, y)))) {
                return false;
            }
        }
    }

    return true;
}

Image::ImageBaseType Image::type() const{

    return imgType;
}

void Image::setWindowCenter(const uint16_t &w_Center){

    this->w_Center = w_Center;
}

void Image::setWindowWidth(const uint16_t &w_Width){

    this->w_Width = w_Width;
}

void Image::setType(const Image::ImageBaseType &imgType){

    this->imgType = imgType;
}

