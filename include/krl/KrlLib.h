#ifndef KRLLIB_HPP
#define KRLLIB_HPP

#include <ImageBase.h>
#include <KrlFileHandler.h>

struct KrlHeaderType {
       
    uint16_t headerType;
    char filename[32];
    uint16_t width;
    uint16_t height;
    char pixBytes;
    char pixBits;
    char OS;
    char compress;
    uint16_t compParas[5];
    char hdtime[32];
    char imgType;
    char black;
    uint16_t pixSize;
    uint16_t sampType;
    char optDensity;
    char dayNo[13];
    long medHistNo;
    char studyType[10];
    char patientName[50];
    char special[216];
    char comment[128];
};


class KRLImage : public Image{

    private:            
        KrlHeaderType header;
        
    public:
        KRLImage();
        KRLImage(std::string filename);
        virtual ~KRLImage();
        
        void openImage(std::string filename) throw (std::runtime_error);
        
        KRLImage* clone();
};

#endif
