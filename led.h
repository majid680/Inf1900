#pragma once
#include <avr/io.h>

class Led {

    private:

    volatile uint8_t* port;
    const uint8_t pin1;
    const uint8_t pin2;


    public:

    Led(volatile uint8_t* port, uint8_t pin1, uint8_t pin2);

    void red();

    void green();

    void off();

    void amber(); //needs a loop to repeat itself for it to work

};