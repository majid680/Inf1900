#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
#include "initialization.h"

const uint8_t DELAYAMBERLED = 8;

Led::Led(volatile uint8_t* port, uint8_t pin1, uint8_t pin2): 
port(port), pin1(pin1), pin2(pin2), color(LedColor::off)
{
    Initialization::setOutput(port, pin1, pin2);
}


void Led::red(){
    *port &= ~(1 << pin1);
    *port |= (1 << pin2);
    color = LedColor::red;
}

void Led::green(){
    *port |= (1 << pin1);
    *port &= ~(1 << pin2);
    color = LedColor::green;
}

void Led::off(){
    *port &= ~(1 << pin1);
    *port &= ~(1 << pin2);
    color = LedColor::off;
}

void Led::amber(){
green();
_delay_ms(DELAYAMBERLED);
red();
_delay_ms(DELAYAMBERLED);
color = LedColor::amber;
}

LedColor Led::getColor(){
    return color;
}