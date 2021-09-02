#include <Pixel.h>

/**
* Constructor
*/
Pixel::Pixel() {

    setRGBPixelValue(0, 0, 0);
    setGrayPixelValue(0);
}

/**
* Constructor
*
* @param r: Red value of the pixel.
* @param g: Green value of the pixel.
* @param b: Blue value of the pixel.
*/
Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b) {
    setRGBPixelValue(r, g, b);
    toGrayScale();
}

/**
* Full Constructor for alpha value
*
* @param r: Red value of the pixel.
* @param g: Green value of the pixel.
* @param b: Blue value of the pixel.
* @param alpha: Alpha value of the pixel.
* @param grayValue: The gray value of the pixel.
*/
Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, float grayPixel){

    setRGBPixelValue(r, g, b);
    setGrayPixelValue(grayPixel);
}

/**
* Constructor of gray Pixel.
*
* @param grayValue: The gray value of the pixel.
*/
Pixel::Pixel(float grayValue) {
    setRGBPixelValue(0, 0, 0);
    setGrayPixelValue(grayValue);
}

/**
* Clone-Constructor.
*/
Pixel::Pixel(const Pixel & pixel) {
    r = pixel.getRedPixelValue();
    g = pixel.getGreenPixelValue();
    b = pixel.getBluePixelValue();
    grayPixel = pixel.getGrayPixelValue();
}

/**
* Destructor.
*/
Pixel::~Pixel() {
}

/**
* Sets a red value of the pixel.
*
* @param r: A red value of the pixel.
*/
void Pixel::setRedPixelValue(uint8_t r) {
    this->r = r;
}

/**
* Sets a green value of the pixel.
*
* @param g: A green value of the pixel.
*/
void Pixel::setGreenPixelValue(uint8_t g) {
    this->g = g;
}

/**
* Sets a blue value of the pixel.
*
* @param b: A blue value of the pixel.
*/
void Pixel::setBluePixelValue(uint8_t b) {
    this->b = b;
}

/**
* Sets a RGB value of the pixel.
*
* @param r: Red value of the pixel.
* @param g: Green value of the pixel.
* @param b: Blue value of the pixel.
*/
void Pixel::setRGBPixelValue(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

/**
* Sets a gray pixel value and the leves of gray.
*
* @param grayValue: The gray value.
* @param grayLevels: The levels of gray.
*/
void Pixel::setGrayPixelValue(float grayValue) {

    grayPixel = grayValue;
}
/**
* Converts a pixel to gray scale.
*/
void Pixel::toGrayScale() {

    if ((getRedPixelValue() == getBluePixelValue()) && (getRedPixelValue() == getGreenPixelValue()) && (getBluePixelValue() == getGreenPixelValue())){
        setGrayPixelValue(getRedPixelValue());
    } else {
        setGrayPixelValue((getBluePixelValue()*0.114) + (getGreenPixelValue()*0.587) + (getRedPixelValue()*0.299));
    }
}


/**
* Gets a gray pixel value.
*
* @return A gray pixel value.
*/
float Pixel::getGrayPixelValue() const {

    return grayPixel;
}

/**
* Gets a red pixel value.
*
* @return A red pixel value.
*/
uint8_t Pixel::getRedPixelValue() const {

    return r;
}

/**
* Gets a green pixel value.
*
* @return A green pixel value.
*/
uint8_t Pixel::getGreenPixelValue() const {

    return g;
}

/**
* Gets blue pixel value.
*
* @return The blue value of the pixel.
*/
uint8_t Pixel::getBluePixelValue() const {

    return b;
}

/**
* Clones a pixel.
*
* @return A cloned pixel.
*/
Pixel * Pixel::clone() const {
    return new Pixel(*this);
}

/**
* Makes a comparison between two pixels.
*
* @return True if the pixels are equal.
*/
bool Pixel::isEqual(const Pixel & p) const {
    return ((p.getRedPixelValue() == r) &&
            (p.getGreenPixelValue() == g) &&
            (p.getBluePixelValue() == b) &&
            (p.getGrayPixelValue() == grayPixel));
}
