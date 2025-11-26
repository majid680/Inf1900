/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                  report class                  #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>
#include "symbol.h"


class Report // ============================= IF IT DOESNT WORK ITS PROBABLY PATHFOUND ===============================
{
    public:
        static void saveReportInEeprom();
        static void sendReportViaUART();
        //static uint8_t pathFound;             //just for test in main
       
        

    private:
        Report() = delete;
        static char pathData[];
        static const char* report[];
        static bool directedLeft;
        static uint16_t addressEeprom;
        static uint8_t pathFound;

        static void reportFindPath();
        static void findAddrEeprom();
        static void createEepromReadyData();
        static void organiseDataForEeprom();
        static void writeDataInEeprom();
        
        static const char* dataToString(uint8_t data, bool rightSide = false);
        static void spaceForFormatting(uint8_t& reportLineIndex);

        static void createReport();



};


