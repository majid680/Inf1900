#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "inputOutput.h"

ValuePrescaler Timer1::prescaler = ValuePrescaler::div8;
volatile uint32_t Timer1::timerCounter = 0;



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
    if (time <= MAX_TIME_PRESCALER8)
        setPrescaler(ValuePrescaler::div8);
    else if (time <= MAX_TIME_PRESCALER64)
        setPrescaler(ValuePrescaler::div64);
    else if (time <= MAX_TIME_PRESCALER256)
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

    uint32_t prescalerValue = static_cast<uint16_t>(prescaler);
    uint32_t OCR1Avalue = (F_CPU * time) / (prescalerValue * SECOND_IN_MS) - 1;
    if (OCR1Avalue > MAX_OCR1A)
        OCR1Avalue = MAX_OCR1A;
    OCR1A = OCR1Avalue;

    TIMSK1 |= (1 << OCIE1A);
    resetTimerCounter();
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


/*============================================================================================================================*/


ValuePrescaler Timer0::prescaler = ValuePrescaler::div1; // default value

void Timer0::setPrescaler(ValuePrescaler valuePrescaler){
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); //clearing up the prescaler bits
    switch (valuePrescaler){
        case ValuePrescaler::div1:
            TCCR0B |= (1 << CS00);
            break;
        case ValuePrescaler::div8:
            TCCR0B |= (1 << CS01);
            break;
        case ValuePrescaler::div64:
            TCCR0B |= (1 << CS00) | (1 << CS01);
            break;
        case ValuePrescaler::div256:
            TCCR0B |= (1 << CS02);
            break;
        case ValuePrescaler::div1024:
            TCCR0B |= (1 << CS02) | (1 << CS00);
            break;
    }
    prescaler = valuePrescaler;
}


void Timer0::findPrescaler(uint32_t frequency)
{
    if (frequency >= MIN_FREQ_PRESCALER1)
        setPrescaler(ValuePrescaler::div1);
    else if (frequency >= MIN_FREQ_PRESCALER8)
        setPrescaler(ValuePrescaler::div8);
    else if (frequency >= MIN_FREQ_PRESCALER64)
        setPrescaler(ValuePrescaler::div64);
    else if (frequency >= MIN_FREQ_PRESCALER256)
        setPrescaler(ValuePrescaler::div256);
    else
        setPrescaler(ValuePrescaler::div1024);
}


void Timer0::setFrequency(uint32_t frequency){
    findPrescaler(frequency);
    TCCR0A |= (1 << COM0A0);
    uint32_t OCR0Avalue = (F_CPU / (static_cast<uint16_t>(prescaler) * frequency * CYCLE_PER_PERIOD)) - 1;
    if (OCR0Avalue > MAX_OCR0A)
        OCR0Avalue = MAX_OCR0A;
    OCR0A = OCR0Avalue;
}

void Timer0::initializationTimer(){
    TCCR0A |= (1 << WGM01); //setting CTC mode, toggle OC0A on compare match, but doesnt initiate the output yet
    InputOutput::setOutput(&PORTB, PB3); //OC0A on PB3
}

void Timer0::stopTimer(){
    TCCR0A &= ~(1 << COM0A0); //disconnecting OC0A pin
}

void Timer0::resumeTimer(){
    TCCR0A |= (1 << COM0A0); //reconnecting OC0A pin
}