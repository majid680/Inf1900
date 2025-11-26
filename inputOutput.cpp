#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "inputOutput.h"


void InputOutput::setInput(volatile uint8_t* port, uint8_t pin){
    if (port == &PINA)
        DDRA &= ~(1 << pin);
    else if (port == &PINB)
        DDRB &= ~(1 << pin);
    else if (port == &PINC)
        DDRC &= ~(1 << pin);
    else if (port == &PIND)
        DDRD &= ~(1 << pin);
}

void InputOutput::setOutput(volatile uint8_t* port, uint8_t pin){
    if (port == &PORTA)
        DDRA |= (1 << pin);
    else if (port == &PORTB)
        DDRB |= (1 << pin);
    else if (port == &PORTC)
        DDRC |= (1 << pin);
    else if (port == &PORTD)
        DDRD |= (1 << pin);
}


void InputOutput::setOutput(volatile uint8_t* port, uint8_t pin1, uint8_t pin2){
    setOutput(port, pin1);
    setOutput(port, pin2);
}

void InputOutput::outputValue1(volatile uint8_t* port, uint8_t pin){
    *port |= (1 << pin);
}
    
void InputOutput::outputValue0(volatile uint8_t* port, uint8_t pin){
    *port &= ~(1 << pin);
}
    
bool InputOutput::readInput(volatile uint8_t* port, uint8_t pin)
{
    if (*port & (1 << pin))
    {
        return true;
    }
    return false;
}