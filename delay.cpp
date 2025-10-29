#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "delay.h"

void Delay::dynamicDelay(uint16_t time){
    for (uint16_t i = 0; i < time; i++)
        _delay_ms(1);
}