/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                    Symbols                     #
#                                                #
#                                                #
################################################*/
#pragma once
#include <avr/io.h>
#include "sensors.h"
#include "led.h"

enum class SensorState
{
    WAIT_WHITE,
    WAIT_LINE,
    END
};

enum class DetectedSymbol {
    PIEZO,
    LED,
    MOTOR,
    SWITCH,
    ERROR  
};

class Symbol
{
public:
    static void findMatchingBlackSymbol();

private:
    static DetectedSymbol lastVisitedSymbol;
    
    static void storeSymbol();
    static void identifySymbol(uint16_t time);

    static SensorState sensorsState;

   
};
