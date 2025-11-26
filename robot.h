/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                  robot class                   #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>
#include "symbol.h"
#include "button.h"
#include "led.h"

enum class BetweenSymbols : uint8_t {STARTING_POINT=1, TAPE = 2, UNKNOWN = 2, POLE =3};

class Robot
{
    public:
        static void initializationOfMaterials();
        static bool findLine();
        static void followLine(); 
        static void goToLine(uint16_t time, bool scan = true);
        static void switchDetected();
        static void symbolDetection();
        static DetectedSymbol getLastVisitedSymbol();

        static void start();


        static uint8_t symbolVisitedCounter;
        static bool symbolBehavior;
        static bool redTape;


        static DetectedSymbol detectedSymbols[];
        static BetweenSymbols betweenSymbols[];
        static const uint8_t MAX_SPEED = 45;

        static Led led;  //pour tests


    private:

        static Button button;
        //static Led led;

        static const uint8_t GOAL = 128;
        static const uint8_t MAX_ERROR = 102;
        static uint8_t lastError;
        static const uint8_t KP = (100 * MAX_SPEED) / MAX_ERROR; // * 100 : we cant use double
        static const uint8_t KD = 10;  // we can change it essai erreur

        static bool leftCorrection;
        static const uint16_t  TIME_TO_PASS_TAPE = 1300;


        static void poleIfPiezo();
        static void poleIfSwitch();
        static void poleIfLed();
        static void poleIfMotor();
        static void redTape();


        static void correct(uint8_t absoluteValueError);
        static uint8_t computeError(uint8_t position);



        Robot() = delete;
};


