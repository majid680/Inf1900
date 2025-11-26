#define F_CPU 8000000UL
#include <avr/io.h>
#include "sound.h"
#include "inputOutput.h"

//Set on timer 0

const uint16_t Sound::frequencies[] = {
        110, 117, 123, 131, 139, 147, 156, 165, 175, 185,
        196, 208, 220, 233, 247, 262, 277, 294, 311, 330,
        349, 370, 392, 415, 440, 466, 494, 523, 554, 587,
        622, 659, 698, 740, 784, 831, 880
    };

void Sound::initializeSound()
{
    Timer0::initializationTimer();
    InputOutput::setOutput(&PORTB, PB5); // PB5 -> low pin
    InputOutput::outputValue0(&PORTB, PB5);
}

void Sound::generateMidiTone(uint8_t key)
{
    if (key < 45 || key > 81) return;
    generateTone(frequencies[key - 45]);
}

void Sound::generateTone(uint16_t frequency){
    Timer0::setFrequency(frequency);
}

void Sound::stopTone()
{
    Timer0::stopTimer();
}
