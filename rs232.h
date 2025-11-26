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
    public:
        static void initializationUART();
        static void readViaUART(const char* display); //For strings
        static void readViaUART(uint16_t display); //For numbers
        static void readViaUART(const char* display, uint8_t size); //To read a specific size from a char array (not null-terminated \0)
        
        static uint8_t receiveUART();

    private:
        static const uint8_t MAX_SIZE_BUFFER = 16;
        static const uint8_t BASE_10 = 10;
        static const uint16_t BAUD = 0xCF;
        
        SerialCommunication() = delete;
        static void transmissionUART(uint8_t value);
};