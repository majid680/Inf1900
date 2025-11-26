/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                   LED class                    #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>


// *********************************** PA0 on - and PA1 on + ************************************

enum class InterpretationLed: uint8_t
{
   vert = 1,
   rouge = 2,
};


enum class LedColor {red, green, amber, off};

class Led {
    public:
        Led(volatile uint8_t* port, uint8_t pin1, uint8_t pin2);

        void turnOnLedInstruction(uint8_t color);
        void red();
        void green();
        void off();
        void amber(); //needs a loop to repeat itself for it to work

        LedColor getColor();

    private:
        volatile uint8_t* port;
        const uint8_t PIN_1;
        const uint8_t PIN_2;
        LedColor color;

};