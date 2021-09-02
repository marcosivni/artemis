#ifndef PNGLIB_HPP
#define PNGLIB_HPP

#include <ImageBase.h>
#include <QPixmap>
#include <QImage>

class PNGImage : public Image{

    private:
        void loadPixelMatrix() throw (std::runtime_error);

    public:
        PNGImage();
        PNGImage(std::string filename);
        virtual ~PNGImage();
  
        void openImage(std::string filename) throw (std::runtime_error);
        
        PNGImage* clone();
};

#endif

