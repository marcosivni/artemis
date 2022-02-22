#include "DcmLib.h"

DCMImage::DCMImage() {
    imgData.clear();
}

DCMImage::DCMImage(std::string filename) {

    openImage(filename);
}

DCMImage::~DCMImage() {

    imgData.clear();
}

void DCMImage::openDataSet(std::string filename){

    //Set filename
    setFilename(filename);
    //Set constants
    setChannels(3);
    setImageID(0);

    // @to-do Add support colored images tag 0028,2002
    uint16_t aux;
    std::vector<unsigned short> pData;
    unsigned short *pixelData;
    float value, a, b;
    Pixel pixel;
    std::string t1;

    imgData(dicom::TAG_PIXEL_DATA) >> pData;
    imgData(dicom::TAG_ROWS) >> aux;
    setHeight(aux);
    imgData(dicom::TAG_COLUMNS) >> aux;
    setWidth(aux);
    imgData(dicom::TAG_BITS_ALLOC) >> aux;
    setBitsPerPixel(aux);

    createPixelMatrix(getWidth(), getHeight());
    pixelData = pData.data();

    try{
        imgData(dicom::TAG_RESCALE_SLOPE) >> t1;
        a = QString(t1.c_str()).toDouble();
        imgData(dicom::TAG_RESCALE_INTERCEPT) >> t1;
        b = QString(t1.c_str()).toDouble();
    } catch (dicom::TagNotFound tt){
        a = 1.0;
        b = 0.0;
        setWindowedPixels(false);
    }

    for (unsigned y = 0; y < getHeight(); y++) {
        for (unsigned x = getWidth(); x > 0; --x) {
            if (getBitsPerPixel() <= 8) {
                value = *((uint8_t *) pixelData);
                pixel.setGrayPixelValue((a*value) + b);
            } else {
                if (getBitsPerPixel() <= 16) {
                    value = *((uint16_t *) pixelData);
                    pixel.setGrayPixelValue((a*value) + b);
                } else {
                    throw new std::runtime_error("Dicom images with more than 16b-depth are not supported!");
                }
            }
            pixelData ++;
            setPixel((getWidth() - x), y, pixel);
        }
    }

    pData.clear();
};

void DCMImage::openImage(std::string filename) {

    std::string tagBuffer, photometric;
    uint16_t c, w;

    imgData.clear();
    setType(Image::DICOM);

    try {
        //Load image-only related meta-info
        dicom::Read(filename, imgData);
        openDataSet(filename);


        imgData(dicom::TAG_WINDOW_CENTER) >> tagBuffer;
        c = (uint16_t) QString(tagBuffer.c_str()).toDouble();
        imgData(dicom::TAG_WINDOW_WIDTH) >> tagBuffer;
        w = (uint16_t) QString(tagBuffer.c_str()).toDouble();
        imgData(dicom::TAG_PHOTOMETRIC) >> photometric;

        setPhotometric(photometric == "MONOCHROME1");
        setWindowCenter(c);
        setWindowWidth(w);

    } catch (std::exception e){
    }


}

void DCMImage::openImage(std::string filename, QByteArray dataStream){

    std::string tagBuffer, photometric;
    uint16_t c, w;

    imgData.clear();
    setType(Image::DICOM);

    try {
        //Load image-only related meta-info
        //std::istream data;
        dicom::Read(dataStream.toStdString().c_str(), imgData);
        openDataSet(filename);

        imgData(dicom::TAG_WINDOW_CENTER) >> tagBuffer;
        c = (uint16_t) QString(tagBuffer.c_str()).toDouble();
        imgData(dicom::TAG_WINDOW_WIDTH) >> tagBuffer;
        w = (uint16_t) QString(tagBuffer.c_str()).toDouble();
        imgData(dicom::TAG_PHOTOMETRIC) >> photometric;

        setPhotometric(photometric == "MONOCHROME1");
        setWindowCenter(c);
        setWindowWidth(w);

    } catch (std::exception e){
    }
}


DCMImage * DCMImage::clone() {
    return new DCMImage(*this);
}


void DCMImage::setTag(dicom::Tag tag, std::string & tagValue) {

    //@to-do Implement operator overload
    //imgData(tag) << tagValue;
}

std::string DCMImage::getTag(dicom::Tag tag) const {

    std::string answer = 0;

    imgData(tag) >> answer;
    return answer;
}
