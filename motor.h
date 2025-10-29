/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                 motor class                    #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>

//OC2A for RIGHT wheel ***
//OC0B for LEFT wheel ***
//Set on timer 2
// PD7 pwm, PD5 direction of RIGHT wheel
// PD6 pwm, PD4 direction of LEFT wheel

enum class Direction{forward, backward};

class Motor{

    private:
    Motor() = delete;

    static const uint8_t maxPower = 100;

    static const uint8_t timerTop = 255;


    static uint8_t setPower(uint8_t power);

    public:

    static void setMotor(); //OC2A on PD7 and OC2B on PD6
           

    static void leftWheel(uint8_t power, Direction direction); //power : from 0 to 100% and direction : Direction::foward or Direction::backward
    static void rightWheel(uint8_t power, Direction direction);
    static void bothWheels(uint8_t power, Direction direction);

    static void turnRight();  //team 32s robot needs ?? ms to turn 90 left and ?? ms to turn 90 right
    static void turnLeft();   //team 42s robot needs ?? ms to turn 90 left and ?? ms to turn 90 right

    static void stopLeft();
    static void stopRight();
    static void stop();


};