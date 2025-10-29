/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                  debug macro                   #
#                                                #
#                                                #
################################################*/

#pragma once
#include "rs232.h"

// Need to initialize SerialCommunication in .cpp to to be able to use debug

#ifdef DEBUG

# define DEBUG_PRINT(x) SerialCommunication::readFlash(x) // ou par RS-232

#else

# define DEBUG_PRINT(x) do {} while (0) // code mort

#endif