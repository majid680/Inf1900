#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer.h"

ValuePrescaler Timer1::prescaler = ValuePrescaler::div8;
uint32_t Timer1::timerCounter = 0;


void Timer1::setPrescaler(ValuePrescaler valuePrescaler){
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); //clearing up the prescaler bits
    switch (valuePrescaler){
        case ValuePrescaler::div1:
            TCCR1B |= (1 << CS10);
            break;
        case ValuePrescaler::div8:
            TCCR1B |= (1 << CS11);
            break;
        case ValuePrescaler::div64:
            TCCR1B |= (1 << CS10) | (1 << CS11);
            break;
        case ValuePrescaler::div256:
            TCCR1B |= (1 << CS12);
            break;
        case ValuePrescaler::div1024:
            TCCR1B |= (1 << CS12) | (1 << CS10);
            break;
    }
    prescaler = valuePrescaler;
}

void Timer1::findPrescaler(uint16_t time)
{
    if (time <= maxTimeForPrescaler8)
        setPrescaler(ValuePrescaler::div8);
    else if (time <= maxTimeForPrescaler64)
        setPrescaler(ValuePrescaler::div64);
    else if (time <= maxTimeForPrescaler256)
        setPrescaler(ValuePrescaler::div256);
    else
        setPrescaler(ValuePrescaler::div1024);

}

void Timer1::startCounter(uint16_t time){
    cli();
    TCCR1B = 0; //to clear the register
    TCNT1 = 0;
    TCCR1A = 0;
    TCCR1B |= (1 << WGM12);
    TCCR1C = 0;         

    findPrescaler(time);

    // TODO: find the right value for OCR1A depending on the value of the chosen prescaler and the time in ms
    uint32_t prescalerValue = static_cast<uint16_t>(prescaler);
    uint32_t OCR1Avalue = (F_CPU / (prescalerValue * secondInMs)) * time;
    if (OCR1Avalue > maxOCR1A)
        OCR1Avalue = maxOCR1A;
    OCR1A = OCR1Avalue;

    TIMSK1 |= (1 << OCIE1A);
    sei();
}

void Timer1::stopTimer(){
    TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
}
    
void Timer1::resumeTimer(){
    setPrescaler(prescaler);
}

void Timer1::resetTimerCounter(){
    timerCounter = 0;
}

uint32_t Timer1::getTimerCounter(){
    return timerCounter;
}

void Timer1::incTimerCounter(){
    timerCounter++;
}


