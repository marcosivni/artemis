#include <KrlLib.h>

KRLImage::KRLImage(){
                
    setFilename("NO_FILE");
    setType(ImageBaseType::KRL);
    setChannels(0);
    setImageID(0);
    setBitsPerPixel(12);
    setWindowCenter(2017);
    setWindowWidth(1562);
}

KRLImage::KRLImage(std::string filename){

    setType(ImageBaseType::KRL);
    setFilename(filename);
    openImage(filename);
    setWindowCenter(2017);
    setWindowWidth(1562);
}

KRLImage::~KRLImage(){
}

void KRLImage::openImage(std::string filename) throw (std::runtime_error){
    
    KrlHeaderType header;
     
    try{
        KrlFileHandler * img = new KrlFileHandler(filename, img->FILE_BINARY);
        
        //==================== HEADER ================================        
        header.headerType = *((uint16_t *)img->readFile(2));
        img->endianSwap(header.headerType);
    
        for(int i=0; i<32; i++)
            header.filename[i] = *(img->readFile(1));
    
    
        header.width = *((uint16_t *) img->readFile(2));
        img->endianSwap(header.width);
    
        header.height = *((uint16_t *) img->readFile(2));
        img->endianSwap(header.height);
     
        header.pixBytes = *(img->readFile(1));
        header.pixBits  = *(img->readFile(1));
        header.OS       = *(img->readFile(1));
        header.compress = *(img->readFile(1));

        for(int i=0;i<5;i++){     
           header.compParas[i] = *((uint16_t *) img->readFile(2));
           img->endianSwap(header.compParas[i]);
        }
    
    for(int i=0; i<32; i++)
         header.hdtime[i] = *(img->readFile(1));
     
     header.imgType = *(img->readFile(1));
     header.black   = *(img->readFile(1));
     
     header.pixSize = *((uint16_t*) img->readFile(2));
     img->endianSwap(header.pixSize);
     
     header.sampType = *((uint16_t*)img->readFile(2));
     img->endianSwap(header.sampType);
     
     header.optDensity = *(img->readFile(1));
    
     for(int i=0; i<13; i++)
         header.dayNo[i] =  *(img->readFile(1));
     
     header.medHistNo = *((long*) img->readFile(4));
     
     for(int i=0; i<10; i++)
         header.studyType[i]   = *(img->readFile(1));
     for(int i=0; i<50; i++)
         header.patientName[i] = *(img->readFile(1));
     for(int i=0; i<216; i++)
         header.special[i]     = *(img->readFile(1));
     for(int i=0; i<128; i++)
         header.comment[i]     = *(img->readFile(1));   
     
     //========================= END HEADER =================================
     //======================== BODY ================================   
     uint16_t tmpValue;
     
     deletePixelMatrix();
     try{
        createPixelMatrix( (uint32_t) header.width, (uint32_t) header.height);
     } catch (...) {
        throw std::runtime_error("Cannot create pixel matrix on krl image.");
     }
     
     for(int x=0; x< header.width; x++){ 
         for(int y=0; y<header.height; y++){
             tmpValue = *((uint16_t *) img->readFile(2));
             img->endianSwap(tmpValue);   
             Pixel aux;
             aux.setGrayPixelValue((float) tmpValue );
             setPixel(x,y,aux);
         }
     }
    setFilename(filename);
    setImageID(2);
    setChannels(0);
    setBitsPerPixel(header.pixBits - 0);
         
    } catch (...) {
        throw std::runtime_error("Cannot open .krl file!");
    }
}

KRLImage* KRLImage::clone(){

    return new KRLImage(*this);
}
