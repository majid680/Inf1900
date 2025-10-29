/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                 rs232 class                    #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>
#include "memoire_24.h"
#include <stdio.h>

class SerialCommunication
{
    private:
        SerialCommunication() = delete;
        static void transmissionUART(uint8_t value);
        static const uint8_t maxSizeBuffer = 16;
        static const uint8_t base10 = 10;
        static const uint16_t baud = 0xCF;
    public:
        static void initializationUART();
        static void readFlash(const char* display); //For strings
        static void readFlash(uint16_t display); //For numbers
};