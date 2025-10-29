/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#              initialization class              #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>

class Initialization{

    private:

    Initialization() = delete;

    public:
    
    static void setInput(volatile uint8_t* port, uint8_t pin);
    static void setOutput(volatile uint8_t* port, uint8_t pin);
    static void setOutput(volatile uint8_t* port, uint8_t pin1, uint8_t pin2);

};
