#pragma once
#include <avr/io.h>

//only with timer1 on OC1A for now***********

class Pwm{

    private:
    static const uint8_t prescaler8 = 8;
    static const uint8_t cyclePerPeriod = 2;
    static const uint8_t maxRatio = 100;
    static uint16_t top;
    static uint8_t ratio;

    public:
    Pwm() = delete;
    
    static void setPwm(uint16_t frequency = 1000); //OC1A on PD5

    static void setFrequency(uint16_t frequency);

    static void setOnRatio(uint8_t ratio); // ratio (%) of time on  vs time off

    static void stop();


};