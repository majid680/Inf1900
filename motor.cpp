#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"
#include "1900util.h"

//Set on timer 2
// PD7 pwm, PD5 direction of right wheel
// PD6 pwm, PD4 direction of left wheel

uint8_t Motor::setPower(uint8_t power){
    if (power > maxPower) 
        power = maxPower;
    return (power*timerTop)/maxPower;
}

void Motor::setMotor(){   
    Initialization::setOutput(&PORTD, PD5, PD7);
    Initialization::setOutput(&PORTD, PD4, PD6);

    TCCR2A |= (1 << WGM20) | (1 << COM2A1) | (1 << COM2B1);    //mode 1 (p.103)

    TCCR2B |= (1 << CS21);  // F_CPU/8 = 1'000'000
}

void Motor::leftWheel(uint8_t power, Direction direction){
    OCR2B = setPower(power);
    if (direction == Direction::backward) //if PD4 = 1 its backward
        PORTD |= (1 << PD4);
    else
        PORTD &= ~(1 << PD4);
}

void Motor::rightWheel(uint8_t power, Direction direction){
    OCR2A = setPower(power);
    if (direction == Direction::backward) //if PD5 = 1 its backward
        PORTD |= (1 << PD5);
    else
        PORTD &= ~(1 << PD5);
}

void Motor::bothWheels(uint8_t power, Direction direction){
    leftWheel(power, direction);
    rightWheel(power, direction);
}

void Motor::stopLeft(){
    OCR2B = 0;
}

void Motor::stopRight(){
    OCR2A = 0;
}

void Motor::stop(){
    stopLeft();
    stopRight();
}