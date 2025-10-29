/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                  delay class                   #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>

class Delay{

    private:

    Delay() = delete;

    public:

    static void dynamicDelay(uint16_t time); //in milliseconds (can wait a max of approx. 65 seconds)

};