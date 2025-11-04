/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                     Code TP9                   #
#                                                #
#                                                #
################################################*/
/* 
This test code starts the the button is pressed using the Button class,
it makes the led change its color every 0.5 sec using the Timer1 and Led classes, 
it makes both wheels turn and then stop every 2 sec using the Delay and Motor classes
it sends a debug message when the .cpp is compiled and installed using "make debug"

Config:
PA0 and PA1 to the LED pin
PD7 on Enable, PD5 on Direction of RIGHT wheel
PD6 on Enable, PD4 on Direction of LEFT wheel
*/

#define F_CPU 8000000UL

#include "debug.h"
#include "interpretationOfInstruction.h"


int main()
{
    InterpretationOfInstruction::initializationOfMaterials();
    Eeprom::writeProgram();
}