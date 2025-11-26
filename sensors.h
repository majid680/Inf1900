/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#            Distance measuring sensor           #
#                                                #
#                                                #
################################################*/
#pragma once
#include <avr/io.h>
#include "can.h"
#include "inputOutput.h"

// enum class Shape 

class Sensor
{
    public:
        static can analogToDigital;
        // static findShape();
    protected:
        // static can analogToDigital;
    private:
        Sensor() = delete;
        
};


class DistanceSensor : private Sensor
{
    public:
        static void detectDistance();
        static void setCaptor();
        static uint8_t getDistance();
        static bool past10Inches();
        static bool past4Inches();
    private:
        DistanceSensor() = delete;
        static const uint8_t value10Inches = 47;
        static const uint8_t value4Inches = 116;
};



class MakerLine : private Sensor
{
    public:
        static uint8_t getAnalogInput();

        static bool getDigitalInput1();
        static bool getDigitalInput2();
        static bool getDigitalInput3();
        static bool getDigitalInput4();
        static bool getDigitalInput5();

        static bool allBlackDetected();
        static bool allWhiteDetected();
        
        static void setCaptor();

        static bool emptyMiddle();
        static bool emptySides();


    private:
        MakerLine() = delete;
};

