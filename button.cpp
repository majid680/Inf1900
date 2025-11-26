#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "button.h"
#include "inputOutput.h"


    volatile bool Button::isInt0Pressed;
    volatile bool Button::isInt1Pressed;
    volatile bool Button::isInt2Pressed;

Button::Button(volatile uint8_t* port, uint8_t pin, bool isInverted){
    InputOutput::setInput(port, pin);    
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

bool Button::interruptDebounce(volatile uint8_t* port, uint8_t pin){
    _delay_ms(DELAYDEBOUNCER);
    if (*port & (1 << pin)){
        return true;
    }
    return false;
}

void Button::interruptRoutine(ButtonInterruptType type){
    switch (type){
        case ButtonInterruptType::int0:
            isInt0Pressed = interruptDebounce(&PIND, PD2);
            break;
        
        case ButtonInterruptType::int1:
            isInt1Pressed = interruptDebounce(&PIND, PD3);
            break;

        case ButtonInterruptType::int2:
            isInt2Pressed = interruptDebounce(&PINB, PB2);
            break; 
    }
    EIFR |= (1 << INTF0);
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

bool Button::isPressedInterrupt(){
    if(*port == PIND){
        if(pin == PD2){

            if(isInt0Pressed){
                isInt0Pressed = false;
                return true;
            }
            return false;
        }
        else if(pin == PD3){
            if(isInt1Pressed){
                isInt1Pressed = false;
                return true;
            }
            return false;
        }
        
    }
    else if(*port == PINB && pin == PB2){
        if(isInt2Pressed){
            isInt2Pressed = false;
            return true;
        }
        return false;     
    }
    return false;
    
}



/*

ISR exemple

ISR(INT0_vect)
{
    Button::interruptRoutine(ButtonInterruptType::int0);
}

*/
