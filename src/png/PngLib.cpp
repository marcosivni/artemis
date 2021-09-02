#include <PngLib.h>

void PNGImage::loadPixelMatrix() throw (std::runtime_error){

    QPixmap *image = new QPixmap();

    if(image->load(getFilename().c_str())){

        deletePixelMatrix();
        try{
            createPixelMatrix((uint32_t) image->width(), (uint32_t) image->height());
        } catch (...) {
            if (image != nullptr)
                delete (image);

            throw std::runtime_error("Cannot create the pixel matrix for the .png image!");
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

        //PNG is a multi channel colored image
        setChannels(3);

        if (conv != nullptr)
            delete (conv);

    } else {
        throw std::runtime_error("Cannot open the .png image! Filename: " + getFilename());
    }

    if (image != nullptr)
        delete (image);
}

PNGImage::PNGImage(){

    setFilename("NO_FILE");
    setChannels(0);
    setImageID(0);
    setBitsPerPixel(8);
    setType(Image::PNG);
}

PNGImage::PNGImage(std::string filename){

    setType(Image::PNG);
    openImage(filename);
    setBitsPerPixel(8);
}

PNGImage::~PNGImage(){
}

void PNGImage::openImage(std::string filename) throw (std::runtime_error){

    setFilename(filename);
    setImageID(0);

    try{
        loadPixelMatrix();
    }catch(...){
        throw std::runtime_error("Cannot create the pixel matrix for the jpg image!");
    }
}

PNGImage* PNGImage::clone(){

    return new PNGImage(*this);
}
