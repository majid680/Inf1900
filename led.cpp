#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
#include "inputOutput.h"

const uint8_t DELAY_AMBER_LED = 8;

Led::Led(volatile uint8_t* port, uint8_t pin1, uint8_t pin2): 
port(port), PIN_1(pin1), PIN_2(pin2), color(LedColor::off)
{
    InputOutput::setOutput(port, PIN_1, PIN_2);
}


void Led::red(){
    *port &= ~(1 << PIN_1);
    *port |= (1 << PIN_2);
    color = LedColor::red;
}

void Led::green(){
    *port |= (1 << PIN_1);
    *port &= ~(1 << PIN_2);
    color = LedColor::green;
}

void Led::off(){
    *port &= ~(1 << PIN_1);
    *port &= ~(1 << PIN_2);
    color = LedColor::off;
}

void Led::amber(){
    green();
    _delay_ms(DELAY_AMBER_LED);
    red();
    _delay_ms(DELAY_AMBER_LED);
    color = LedColor::amber;
}

LedColor Led::getColor(){
    return color;
}

void Led::turnOnLedInstruction(uint8_t color)
{
    switch(static_cast<InterpretationLed>(color))
    {
        case InterpretationLed::vert:
            green();
            break;
        case InterpretationLed::rouge:
            red();
            break;
        default:
            break;
    }
}