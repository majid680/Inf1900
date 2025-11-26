#define F_CPU 8000000UL
#include <avr/io.h>
#include "symbol.h"
#include "sensors.h"
#include "led.h"
#include "motor.h"
#include "timer.h"
#include "robot.h"
#include "sound.h"
#include "rs232.h"



SensorState Symbol::sensorsState = SensorState::WAIT_WHITE;
DetectedSymbol Symbol::lastVisitedSymbol;


void findDelay(){

}


void Symbol::findMatchingBlackSymbol() //called after allBlack mm si ce lest encore
{
    Motor::bothWheels(Robot::MAX_SPEED, Direction::forward, true);
    while (sensorsState != SensorState::END){
        switch (sensorsState){
            case SensorState::WAIT_WHITE:
                if (MakerLine::allWhiteDetected()){
                    sensorsState = SensorState::WAIT_LINE;
                    Timer1::startCounter(10);   //inc timer counter every 10ms         ======DONT FORGET ISR TO INC COUNTER ===============
                }
                break;
            case SensorState::WAIT_LINE:
                if (!MakerLine::allWhiteDetected()){
                    sensorsState = SensorState::END;
                    Timer1::stopTimer();
                    break;
                }
            default:
                break;
        }
    }
    sensorsState = SensorState::WAIT_WHITE;  //reset for next symbol
    uint16_t time = Timer1::getTimerCounter();
    // while (true)
    //     SerialCommunication::readViaUART(time); //======================================just to find the correct delay (remove later)================================
    identifySymbol(time);
}



void Symbol::storeSymbol()
{
    Robot::detectedSymbols[Robot::symbolVisitedCounter] = lastVisitedSymbol;
    Robot::symbolVisitedCounter++;
}

void Symbol::identifySymbol(uint16_t time)  //======================================Ajust with the correct time values================================
{
    if (time >= 0 && time < 20){    //en centieme de seconde
        lastVisitedSymbol = DetectedSymbol::MOTOR;
        storeSymbol();
    }
    else if (time >= 50 && time < 150){
        lastVisitedSymbol = DetectedSymbol::LED;
        storeSymbol();
    }
    else if (time >= 150 && time < 375){
        lastVisitedSymbol = DetectedSymbol::PIEZO;
        storeSymbol();
    }
    Robot::symbolBehavior = true;
}