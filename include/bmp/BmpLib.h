#ifndef BMPLIB_HPP
#define BMPLIB_HPP

#include <ImageBase.h>
#include <QPixmap>
#include <QImage>

class BMPImage : public Image{

    private:
        void loadPixelMatrix() throw (std::runtime_error);

    public:
        BMPImage();
        BMPImage(std::string filename);
        virtual ~BMPImage();
  
        void openImage(std::string filename) throw (std::runtime_error);
        
        BMPImage* clone();
};

#endif

