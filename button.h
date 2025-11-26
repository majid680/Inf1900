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
    public:
        Button(volatile uint8_t* port, uint8_t pin, bool isInverted = false);  //the port must be &PINX
        bool isPressed();
        bool isPressedInterrupt();
        static void interruptRoutine(ButtonInterruptType type);
        static void enableInterruption(InterruptMode mode, ButtonInterruptType type);      

    private:
        static const uint8_t DELAYDEBOUNCER = 10;

        static volatile bool isInt0Pressed;
        static volatile bool isInt1Pressed;
        static volatile bool isInt2Pressed;

        volatile uint8_t* port;
        uint8_t pin;
        bool inverted;
        static void configEICRA(InterruptMode mode, uint8_t ISCn0, uint8_t ISCn1);
        static bool interruptDebounce(volatile uint8_t* port, uint8_t pin);
};


//Button button(&PIND, PD2); to call the constructor
    