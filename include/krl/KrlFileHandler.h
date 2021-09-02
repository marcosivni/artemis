#ifndef KRLKrlFileHandler_HPP
#define KRLKrlFileHandler_HPP

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <stdexcept>

class KrlFileHandler {
      
    private :
        int size;
        int type;
		
    public :
        std::fstream file;
        static const int FILE_IN = 0;
        static const int FILE_OUT = 1;
        static const int FILE_OUT_APP = 2;
        static const int FILE_BINARY = 3;
		
	public:
        KrlFileHandler();
            KrlFileHandler(std::string name, int type) throw (std::runtime_error);
            ~KrlFileHandler();
		
            void setSize(int size);
		
            int getSize();
            char * getNextLine();
            char * getNextWord(char * &line);
        
            char * readFile(int size);
            char * readBuffer(char * &buffer, int numByte);

            void endianSwap(uint16_t& x);
            void close();
       
            static bool fileExists( std::string fileName);
            bool endOfFile();
		
};

#endif
