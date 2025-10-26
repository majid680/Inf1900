#pragma once
#include <avr/io.h>
#include "memoire_24.h"
#include <stdio.h>

class SerialCommunication
{
    private:
        SerialCommunication() = delete;
        static void transmissionUART(uint8_t donnee);
        static const uint8_t maxSizeBuffer = 16;
        static const uint8_t base10 = 10;

    public:
        static void initialisationUART();
        static void readFlash(const char* display); //For strings
        static void readFlash(uint16_t display); //For numbers
};