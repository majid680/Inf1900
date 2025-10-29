/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                 writeEeprom class              #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>
#include "memoire_24.h"

class writeEeprom
{
    private:
        Memoire24CXXX memory;
        
        char extractedData[];
        bool isIdentical = false;

    public:
        writeEeprom();
        void writeData(uint16_t address, const char* data, uint8_t size);
        bool compareData(uint16_t address, const char* data, uint8_t size);
};