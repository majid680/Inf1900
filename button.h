/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                  Button class                  #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>



enum class InterruptMode{risingEdge, fallingEdge, anyEdge, lowLevel};

enum class ButtonInterruptType{int0, int1, int2};

class Button {


    private:

    volatile uint8_t* port;
    uint8_t pin;
    bool inverted;
    static void configEICRA(InterruptMode mode, uint8_t ISCn0, uint8_t ISCn1);

    public:

    Button(volatile uint8_t* port, uint8_t pin, bool isInverted = false);

    bool isPressed();

    static void enableInterruption(InterruptMode mode, ButtonInterruptType type);  


};


//Button button(&PIND, PD2); to call the constructor
    