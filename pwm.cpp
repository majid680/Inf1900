#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "pwm.h"
#include "1900util.h"

//on timer 1

uint16_t Pwm::top = 0;
uint8_t  Pwm::ratio = 0;  

void Pwm::setPwm(uint16_t frequency){   //frequency in Hz (1000 by default)
    Initialization::setOutput(&PORTD, PD5);

    TCCR1A = 0;
    TCCR1B = 0;  //to clear the registers

    TCCR1A |= (1 << WGM11) | (1 << COM1A1);    //mode 10 (p.130)

    TCCR1B |= (1 << WGM13) | (1 << CS11); 

    TCCR1C = 0;


    setFrequency(frequency);
}

void Pwm::setFrequency(uint16_t frequency){
    top = 8000000UL / (prescaler8 * cyclePerPeriod * frequency);     //with prescaler = 8, f = F_CPU / (8 * 2 * top) -> top = F_CPU / (8 * 2 * f)
    ICR1 = top;
    setOnRatio(ratio); //to get the good OCR1A value for the new top
}

void Pwm::setOnRatio(uint8_t ratio){
    if (ratio > maxRatio) 
        ratio = maxRatio;
    OCR1A = (ratio * top) / maxRatio;  
    Pwm::ratio = ratio;  
}

void Pwm::stop(){
    OCR1A = 0;
}

