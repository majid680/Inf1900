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
    public:
        static void setMotor(); //OC2A on PD7 and OC2B on PD6
        static void bothWheels(uint8_t power, Direction direction, bool isCorrected = false); //power : from 0 to 100% and direction : Direction::foward or Direction::backward
        static void leftWheel(uint8_t power, Direction direction); 
        static void rightWheel(uint8_t power, Direction direction);

        static void turnForward(uint8_t leftPower, uint8_t rightPower, bool boost = false);

        static void turnRight(uint8_t power = MAX_POWER);  
        static void turnLeft(uint8_t power = MAX_POWER);   

        static void turnRightWithDegree(uint16_t time);
        static void turnLeftWithDegree(uint16_t time);

        static void stop();



    private:
        static const uint8_t leftCorrectionValue = 2;   //reduce right drifting
        static const uint8_t rightCorrectionValue = 7;  //reduce left drifting     (about 7% with a leftCorrectionValue of 2)
        static bool isStopped;
        static const uint8_t MAX_POWER = 100;
        static const uint8_t USED_SPEED = 45;
        static const uint8_t TIMER_TOP = 255;
        static const uint16_t TIME_TO_TURN90 = 1500; 
        static const uint16_t TIME_TO_TURN30 = 485; 
        static const uint16_t TIME_TO_TURN15 = 200; 
        static const uint16_t TIME_TO_TURN45 = 700;  

        static void stopLeft();
        static void stopRight();
        static uint8_t setPower(uint8_t power);

        Motor() = delete;

};
