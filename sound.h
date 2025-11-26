/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                 sound class                    #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>
#include "timer.h"
#include "inputOutput.h"


class Sound{
    public:
        static void initializeSound();
        static void generateMidiTone(uint8_t key); //frequency in Hz and duration in ms
        static void generateTone(uint16_t frequency);
        static void stopTone();
        
    private:
        static const uint16_t frequencies[37];

    Sound() = delete;

    
};

