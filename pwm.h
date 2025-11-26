/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                  pwm class                     #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>

//only with timer1 on OC1A for now***********

class PwmTimer1{
    public:
        static void setPwm(uint16_t frequency = 1000); //OC1A on PD5
        static void setFrequency(uint16_t frequency);
        static void setOnRatio(uint8_t ratio); // ratio (%) of time on  vs time off
        static void stop();

    private:
        static const uint8_t PRESCALER_8 = 8;
        static const uint8_t CYCLE_PER_PERIOD = 2;
        static const uint8_t MAX_RATIO = 100;
        static uint16_t top;
        static uint8_t ratio;

        PwmTimer1() = delete;
};
