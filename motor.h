#pragma once
#include <avr/io.h>
#include "1900util.h"

//OC2A for RIGHT wheel ***
//OC0B for LEFT wheel ***
//Set on timer 2
// PD7 pwm, PD5 direction of RIGHT wheel
// PD6 pwm, PD4 direction of LEFT wheel

class Motor{

    private:
    Motor() = delete;

    static const uint8_t maxPower = 100;

    const uint8_t timerTop = 255;


    static uint8_t setPower(uint8_t power);

    public:

    static void setMotor(); //OC2A on PD7 and OC2B on PD6
           

    static void leftWheel(uint8_t power, Direction direction); //power : from 0 to 100% and direction : Direction::foward or Direction::backward
    static void rightWheel(uint8_t power, Direction direction);
    static void bothWheels(uint8_t power, Direction direction);

    static void stopLeft();
    static void stopRight();
    static void stop();


};