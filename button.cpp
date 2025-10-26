#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "button.h"
#include "1900util.h"

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

void Button::enableInterruption(InterruptMode mode, ButtonInterruptType type){
    cli();
    switch (type){
        case ButtonInterruptType::int0:
            switch (mode){
                case InterruptMode::lowLevel:
                    EICRA &= ~((1 << ISC00) | (1 << ISC01));
                    break;
                case InterruptMode::anyEdge:
                    EICRA &= ~(1 << ISC01);
                    EICRA |= (1 << ISC00);
                    break;
                case InterruptMode::fallingEdge:
                    EICRA |= (1 << ISC01);
                    EICRA &= ~(1 << ISC00);
                    break;
                case InterruptMode::risingEdge:
                    EICRA |= (1 << ISC01) | (1 << ISC00);
                    break;
            }
            EIMSK |= (1 << INT0);
            break;
        case ButtonInterruptType::int1:
            switch (mode){
                case InterruptMode::lowLevel:
                    EICRA &= ~((1 << ISC10) | (1 << ISC11));
                    break;
                case InterruptMode::anyEdge:
                    EICRA &= ~(1 << ISC11);
                    EICRA |= (1 << ISC10);
                    break;
                case InterruptMode::fallingEdge:
                    EICRA |= (1 << ISC11);
                    EICRA &= ~(1 << ISC10);
                    break;
                case InterruptMode::risingEdge:
                    EICRA |= (1 << ISC11) | (1 << ISC10);
                    break;
            }
            EIMSK |= (1 << INT1);
            break;
        case ButtonInterruptType::int2:
            switch (mode){
                case InterruptMode::lowLevel:
                    EICRA &= ~((1 << ISC20) | (1 << ISC21));
                    break;
                case InterruptMode::anyEdge:
                    EICRA &= ~(1 << ISC21);
                    EICRA |= (1 << ISC20);
                    break;
                case InterruptMode::fallingEdge:
                    EICRA |= (1 << ISC21);
                    EICRA &= ~(1 << ISC20);
                    break;
                case InterruptMode::risingEdge:
                    EICRA |= (1 << ISC21) | (1 << ISC20);
                    break;
            }
            EIMSK |= (1 << INT2);
            break;
    }
    sei();
}

//dont forget the "EIFR |= (1 << INTF0) ;" at the end of the ISR routine
