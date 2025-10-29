#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "button.h"
#include "initialization.h"

const int DELAYDEBOUNCER = 10;

Button::Button(volatile uint8_t* port, uint8_t pin, bool isInverted){
    Initialization::setInput(port, pin);    
    inverted = isInverted;
    this->port = port;
    this->pin = pin;
}

bool Button::isPressed(){
    if (*port & (1 << pin)){

        _delay_ms(DELAYDEBOUNCER);
        if (*port & (1 << pin)){
            return inverted ? false : true;
        }
    }
    return inverted ? true : false;
}

void Button::configEICRA(InterruptMode mode, uint8_t ISCn0, uint8_t ISCn1){
    switch (mode){
                case InterruptMode::lowLevel:
                    EICRA &= ~((1 << ISCn0) | (1 << ISCn1));
                    break;
                case InterruptMode::anyEdge:
                    EICRA &= ~(1 << ISCn1);
                    EICRA |= (1 << ISCn0);
                    break;
                case InterruptMode::fallingEdge:
                    EICRA |= (1 << ISCn1);
                    EICRA &= ~(1 << ISCn0);
                    break;
                case InterruptMode::risingEdge:
                    EICRA |= (1 << ISCn1) | (1 << ISCn0);
                    break;
            }
}

void Button::enableInterruption(InterruptMode mode, ButtonInterruptType type){
    cli();
    switch (type){
        case ButtonInterruptType::int0:
            configEICRA(mode, ISC00, ISC01);
            EIMSK |= (1 << INT0);
            break;
        case ButtonInterruptType::int1:
            configEICRA(mode, ISC10, ISC11);
            EIMSK |= (1 << INT1);
            break;
        case ButtonInterruptType::int2:
            configEICRA(mode, ISC20, ISC21);
            EIMSK |= (1 << INT2);
            break;
    }
    sei();
}

//dont forget the "EIFR |= (1 << INTF0) ;" at the end of the ISR routine
