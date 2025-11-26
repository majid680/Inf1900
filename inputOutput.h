/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#              InputOutput class                 #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>

class InputOutput{
    public:
        static void setInput(volatile uint8_t* port, uint8_t pin);
        static void setOutput(volatile uint8_t* port, uint8_t pin);
        static void setOutput(volatile uint8_t* port, uint8_t pin1, uint8_t pin2);
        static void outputValue1(volatile uint8_t* port, uint8_t pin);
        static void outputValue0(volatile uint8_t* port, uint8_t pin);
        static bool readInput(volatile uint8_t* port, uint8_t pin);

    private:
        InputOutput() = delete;
};
