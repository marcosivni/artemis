#include <KrlFileHandler.h>

KrlFileHandler::KrlFileHandler(){
}

KrlFileHandler::KrlFileHandler(std::string name, int type) throw (std::runtime_error){

    if (!fileExists(name))
       throw std::runtime_error("The .krl image file cannot be opened or the file does not exists!");
            
    switch(type){
        case 0: //FILE_IN:
            this->file.open(name.c_str(),std::fstream::in);
            break;
        case 1: //FILE_OUT:
            this->file.open(name.c_str(),std::fstream::out);
            break;
        case 2: //FILE_OUT_APP:
            this->file.open(name.c_str(),std::fstream::app);
            break;
        case 3: //FILE_BINARY
            this->file.open(name.c_str(),std::fstream::in | std::fstream::binary);
            break;
    }
    
    this->type = type;
    
    file.seekg(0, std::ios::end);
    setSize(file.tellg());
    file.seekg(0, std::ios::beg);
}

KrlFileHandler::~KrlFileHandler(){
}

void KrlFileHandler::setSize(int size){

    this->size = size;
}

int KrlFileHandler::getSize(){

    return size;
}

char* KrlFileHandler::getNextLine(){
    
    char *charLine;
    std::string line;
    getline(this->file,line);
    charLine = new char[line.size()+1];
    strcpy(charLine, line.c_str());
    
    return charLine;
}

char * KrlFileHandler::getNextWord(char * &line){

    char * begin = line;
    while( *line != ' ' && *line != '\n' && *line != '\0' ){
           
        line++;
    }
    *line = '\0';
    line++;
    return begin;     
}

char * KrlFileHandler::readFile(int size){
    
    char * tmp = new char(size); 
    this->file.read(tmp,size);
    return tmp;     
}

char * KrlFileHandler::readBuffer( char* & buffer, int numByte){
        
    char* tmp = new char[numByte];
    for(int i=0;i<numByte;i++)
        tmp[i] = buffer[i];
    buffer = buffer + numByte;
    return tmp;  
}

void KrlFileHandler::endianSwap(uint16_t& x){
       
    x = (x>>8) | (x<<8);
}


void KrlFileHandler::close(){

    this->file.close();
}

bool KrlFileHandler::fileExists(std::string fileName){
     
    std::fstream tmpFile(fileName.c_str());
    if(tmpFile.is_open()){
        tmpFile.close();
        return true;
    } else {
        return false;       
    }   
     
}

bool KrlFileHandler::endOfFile(){
     
    return(file.eof());
}

