#define F_CPU 8000000UL
#include <avr/io.h>
#include "sensors.h"
#include "can.h"
#include "inputOutput.h"

can Sensor::analogToDigital;

void DistanceSensor::setCaptor()
{
    InputOutput::setInput(&PORTA, PA7);
}

uint8_t DistanceSensor::getDistance()
{
    uint16_t accumulatedValue = 0;
    for (uint8_t measure = 0; measure<20 ; measure++)
    {
        accumulatedValue += (analogToDigital.lecture(PA7) >> 2);
    }
    return (accumulatedValue / 20);
}
// 10 pouce = 47 
// 4 pouce = 116


bool DistanceSensor::past10Inches(){
    if (getDistance() > value10Inches)
        return true;
    return false;
}

bool DistanceSensor::past4Inches(){
    if (getDistance() > value4Inches)
        return true;
    return false;
}


void MakerLine::setCaptor()
{
    InputOutput::setInput(&PORTA, PA0);
    InputOutput::setInput(&PORTA, PA2);
    InputOutput::setInput(&PORTA, PA3);
    InputOutput::setInput(&PORTA, PA4);
    InputOutput::setInput(&PORTA, PA5);
    InputOutput::setInput(&PORTA, PA6);
}

uint8_t MakerLine::getAnalogInput()
{
    return (analogToDigital.lecture(PA0) >> 2);
}

bool MakerLine::getDigitalInput1()
{
    return InputOutput::readInput(&PINA, PA2);
}
bool MakerLine::getDigitalInput2()
{
    return InputOutput::readInput(&PINA, PA3);
}
bool MakerLine::getDigitalInput3()
{
    return InputOutput::readInput(&PINA, PA4);
}
bool MakerLine::getDigitalInput4()
{
    return InputOutput::readInput(&PINA, PA5);
}
bool MakerLine::getDigitalInput5()
{
    return InputOutput::readInput(&PINA, PA6);
}


bool MakerLine::allBlackDetected(){
    uint8_t input = getAnalogInput();
    if (input >= 230)
        return true;
    return false;
}

bool MakerLine::allWhiteDetected(){
    uint8_t input = getAnalogInput();
    if (input <= 26)
        return true;
    return false;
}



bool MakerLine::emptyMiddle()
{
    if (
        getDigitalInput1() == true &&
        getDigitalInput2() == false &&
        getDigitalInput3() == false &&
        getDigitalInput4() == false &&
        getDigitalInput5() == true
    )
    {
        return true;
    }
    return false;
}

bool MakerLine::emptySides()
{
    if (
        ((getDigitalInput1() == false) || (getDigitalInput5() == false)) &&
        getDigitalInput2() == true &&
        getDigitalInput3() == true &&
        getDigitalInput4() == true
    )
    {
        return true;
    }
    return false;
}