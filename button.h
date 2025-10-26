#pragma once
#include <avr/io.h>
#include "1900util.h"


class Button {


    private:

    volatile uint8_t* port;
    uint8_t pin;
    bool inverted;

    public:

    Button(volatile uint8_t* port, uint8_t pin, bool isInverted = false);

    bool isPressed();

    static void enableInterruption(InterruptMode mode, ButtonInterruptType type);  


};


//Button button(&PIND, PD2); to call the constructor
    