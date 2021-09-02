#ifndef JPGLIB_HPP
#define JPGLIB_HPP

#include <ImageBase.h>
#include <QPixmap>
#include <QImage>

class JPGImage : public Image{

    private:
        void loadPixelMatrix() throw (std::runtime_error);

    public:
        JPGImage();
        JPGImage(std::string filename);
        virtual ~JPGImage();
  
        void openImage(std::string filename) throw (std::runtime_error);
        
        JPGImage* clone();
};

#endif

