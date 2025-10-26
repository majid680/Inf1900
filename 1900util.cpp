#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "1900util.h"


void Initialization::setInput(volatile uint8_t* port, uint8_t pin){
    if (port == &PINA)
        DDRA &= ~(1 << pin);
    else if (port == &PINB)
        DDRB &= ~(1 << pin);
    else if (port == &PINC)
        DDRC &= ~(1 << pin);
    else if (port == &PIND)
        DDRD &= ~(1 << pin);
}

void Initialization::setOutput(volatile uint8_t* port, uint8_t pin){
    if (port == &PORTA)
        DDRA |= (1 << pin);
    else if (port == &PORTB)
        DDRB |= (1 << pin);
    else if (port == &PORTC)
        DDRC |= (1 << pin);
    else if (port == &PORTD)
        DDRD |= (1 << pin);
}

void Initialization::setOutput(volatile uint8_t* port, uint8_t pin1, uint8_t pin2){
    Initialization::setOutput(port, pin1);
    Initialization::setOutput(port, pin2);
}

void Delay::dynamicDelay(uint16_t time){
    for (uint16_t i = 0; i < time; i++)
        _delay_ms(Delay::delay);
}