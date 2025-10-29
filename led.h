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

enum class LedColor {red, green, amber, off};

class Led {

    private:

    volatile uint8_t* port;
    const uint8_t pin1;
    const uint8_t pin2;
    LedColor color;


    public:

    Led(volatile uint8_t* port, uint8_t pin1, uint8_t pin2);

    void red();

    void green();

    void off();

    void amber(); //needs a loop to repeat itself for it to work

    LedColor getColor();

};