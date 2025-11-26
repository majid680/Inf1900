/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                 Eeprom class                   #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>
#include "memoire_24.h"
#include "rs232.h"


class Eeprom
{
    public:
        static void writeData(uint16_t address, const char* data, uint8_t size);
        static char* extractFromEeprom(uint16_t address, char* extractedData, uint8_t size);
        static uint8_t findLength(const char* data);
        static void writeProgram();
        static uint16_t getFileSize();
        static uint8_t writeFromSerial(uint16_t startAddress);

    private:
        static Memoire24CXXX memory;
        static const uint16_t STARTING_ADDR = 0x0002;
        static const uint16_t FILE_SIZE_ADDR = 0x0000;
        static const uint8_t SHIFT_LEFT =8;
        static const uint8_t INSTRUCTION_BYTE =2;
        static const uint8_t INCREMENT_ADDR =1;
        static const uint8_t NB_OF_BYTE =1;
        static const char END_OF_STRING = '\0';

        Eeprom() = delete;

};