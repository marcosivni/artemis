#include <BmpLib.h>

void BMPImage::loadPixelMatrix() throw (std::runtime_error){

    QPixmap *image = new QPixmap();

    if(image->load(getFilename().c_str())){

        deletePixelMatrix();
        try{
            createPixelMatrix((uint32_t) image->width(), (uint32_t) image->height());
        } catch (...) {
            if (image != nullptr)
                delete (image);

            throw std::runtime_error("Cannot create the pixel matrix for the .bmp image!");
        }

        QImage *conv = new QImage();
        *conv = image->toImage();
        *conv = conv->convertToFormat(QImage::Format_RGB888);

        for (uint32_t y = 0; y < getHeight(); y++){
            uchar *bits = conv->scanLine(y);
            for (uint32_t x = 0; x < getWidth()*3; x += 3){
              Pixel aux;
              aux.setRedPixelValue(bits[x]);
              aux.setGreenPixelValue(bits[x+1]);
              aux.setBluePixelValue(bits[x+2]);

              if (aux.getBluePixelValue() == aux.getGreenPixelValue() && aux.getGreenPixelValue() == aux.getRedPixelValue()){
                  aux.setGrayPixelValue(aux.getBluePixelValue());
              }

              setPixel(x/3, y, aux);
          }
        }

        //BMP is a multi channel colored image
        setChannels(3);

        if (conv != nullptr)
            delete (conv);

    } else {
        throw std::runtime_error("Cannot open the .bmp image! Filename: " + getFilename());
    }

    if (image != nullptr)
        delete (image);
}

BMPImage::BMPImage(){

    setFilename("NO_FILE");
    setChannels(0);
    setImageID(0);
    setBitsPerPixel(8);
    setType(Image::BMP);
}

BMPImage::BMPImage(std::string filename){

    setType(Image::BMP);
    openImage(filename);
    setBitsPerPixel(8);
}

BMPImage::~BMPImage(){
}

void BMPImage::openImage(std::string filename) throw (std::runtime_error){

    setFilename(filename);
    setImageID(0);

    try{
        loadPixelMatrix();
    }catch(...){
        throw std::runtime_error("Cannot create the pixel matrix for the .bmp image!");
    }
}

BMPImage* BMPImage::clone(){

    return new BMPImage(*this);
}
