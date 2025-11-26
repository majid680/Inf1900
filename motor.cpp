#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"
#include "inputOutput.h"
#include "delay.h"

//Set on timer 2
// PD7 pwm, PD5 direction of right wheel
// PD6 pwm, PD4 direction of left wheel

bool Motor::isStopped = true;

uint8_t Motor::setPower(uint8_t power){
    if (power > MAX_POWER) 
        power = MAX_POWER;
    return (power * TIMER_TOP)/ MAX_POWER;
}

void Motor::setMotor(){   
    InputOutput::setOutput(&PORTD, PD5, PD7);
    InputOutput::setOutput(&PORTD, PD4, PD6);

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

void Motor::bothWheels(uint8_t power, Direction direction, bool isCorrected){
    if (isStopped){
        leftWheel(MAX_POWER, direction);
        rightWheel(MAX_POWER, direction);
        _delay_ms(100);
        isStopped = false;
    }
    if (isCorrected){
        leftWheel(power - (power*leftCorrectionValue)/100, direction);
        rightWheel(power - (power*rightCorrectionValue)/100, direction);
    }
    else {
        leftWheel(power, direction);
        rightWheel(power, direction);
    }
}

void Motor::turnForward(uint8_t leftPower, uint8_t rightPower, bool boost){
    if (isStopped){
        leftWheel(MAX_POWER, Direction::forward);
        rightWheel(MAX_POWER, Direction::forward);
        _delay_ms(100);
        isStopped = false;
    }
    else if(boost){
        leftWheel(MAX_POWER, Direction::forward);
        rightWheel(MAX_POWER, Direction::forward);
        _delay_ms(50);
    }

    leftWheel(leftPower, Direction::forward);
    rightWheel(rightPower, Direction::forward);
}


void Motor::turnLeft(uint8_t power){
    if (isStopped){
        leftWheel(MAX_POWER, Direction::backward);
        rightWheel(MAX_POWER, Direction::forward);
        _delay_ms(100);
        isStopped = false;
    }
    leftWheel(power, Direction::backward);
    rightWheel(power, Direction::forward);
}

void Motor::turnRight(uint8_t power){
    if (isStopped){
        leftWheel(MAX_POWER, Direction::forward);
        rightWheel(MAX_POWER, Direction::backward);
        _delay_ms(100);
        isStopped = false;
    }

    leftWheel(power, Direction::forward);
    rightWheel(power, Direction::backward);
}

void Motor::turnRightWithDegree(uint16_t time){
    if (isStopped){
        leftWheel(MAX_POWER, Direction::forward);
        rightWheel(MAX_POWER, Direction::backward);
        _delay_ms(100);
        isStopped = false;
    }

    leftWheel(USED_SPEED, Direction::forward);
    rightWheel(USED_SPEED, Direction::backward);
    Delay::dynamicDelay(time);
    stop();

}



void Motor::turnLeftWithDegree(uint16_t time){
    if (isStopped){
        leftWheel(MAX_POWER, Direction::backward);
        rightWheel(MAX_POWER, Direction::forward);
        _delay_ms(100);
        isStopped = false;
    }

    leftWheel(USED_SPEED, Direction::backward);
    rightWheel(USED_SPEED, Direction::forward);
    Delay::dynamicDelay(time);
    stop();
    
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
    isStopped = true;
}
