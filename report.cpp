#define F_CPU 8000000UL
#include <avr/io.h>
#include "report.h"
#include "symbol.h"
#include "eeprom.h"
#include "robot.h"
#include "memoire_24.h"


#define PIEZO_STR "-----PIEZO-----"
#define DIODE_STR "-----DIODE-----"
#define MOTEUR_STR "-----MOTEUR-----"
#define INTERRUPTEUR_STR "--INTERRUPTEUR--"
#define NEWLINE "\r\n"

uint8_t Report::pathFound = 0;
char Report::pathData[4];
uint16_t Report::addressEeprom;
const char* Report::report[52];
bool Report::directedLeft;


void Report::saveReportInEeprom(){  

    reportFindPath();                   //     commented to test
    findAddrEeprom();
    createEepromReadyData();
    writeDataInEeprom();
}

void Report::reportFindPath()
{
    switch (Robot::detectedSymbols[0])
    {
        case DetectedSymbol::PIEZO:
        {
            if (Robot::detectedSymbols[1] == DetectedSymbol::LED)
            {
                pathFound = 2;
                directedLeft = false;
            }
            else if (Robot::detectedSymbols[1] == DetectedSymbol::SWITCH)
            {
                pathFound = 3;
                directedLeft = false;
            }
            else if (Robot::detectedSymbols[1] == DetectedSymbol::MOTOR)
            {
                pathFound = 3;
                directedLeft = true;
            }
            break;
        }
        case DetectedSymbol::LED:
        {
            if (Robot::detectedSymbols[1] == DetectedSymbol::SWITCH)
            {
                pathFound = 1;
                directedLeft = true;
            }
            else if (Robot::detectedSymbols[1] == DetectedSymbol::MOTOR)
            {
                pathFound = 2;
                directedLeft = false;
            }
            else if (Robot::detectedSymbols[1] == DetectedSymbol::PIEZO)
            {
                pathFound = 2;
                directedLeft = true;
            }
            break;
        }
        case DetectedSymbol::MOTOR:
        {
            if (Robot::detectedSymbols[1] == DetectedSymbol::PIEZO)
            {
                pathFound = 3;
                directedLeft = false;
            }
            else if (Robot::detectedSymbols[1] == DetectedSymbol::SWITCH)
            {
                pathFound = 1;
                directedLeft = false;
            }
            else if (Robot::detectedSymbols[1] == DetectedSymbol::LED)
            {
                pathFound = 2;
                directedLeft = true;
            }
            break;
        }
        case DetectedSymbol::SWITCH:
        {
            if (Robot::detectedSymbols[1] == DetectedSymbol::LED)
            {
                pathFound = 1;
                directedLeft = false;
            }
            else if (Robot::detectedSymbols[1] == DetectedSymbol::MOTOR)
            {
                pathFound = 1;
                directedLeft = true;
            }
            else if (Robot::detectedSymbols[1] == DetectedSymbol::PIEZO)
            {
                pathFound = 3;
                directedLeft = true;
            }
            break;
        }
        case DetectedSymbol::ERROR:
            break;
    }
}

void Report::findAddrEeprom()
{
    switch (pathFound){
        case 1:
            addressEeprom = 0;
            break;
        case 2:
            addressEeprom = 4;
            break;
        case 3:
            addressEeprom = 8;
            break;
    }
}

void Report::writeDataInEeprom()
{
    // i deleted a memory object cause i think its useless here
    for (uint8_t i=0; i< 4; i++)
    {
        char data = pathData[i];
        Eeprom::writeData(addressEeprom + i, &data, 1);
    }
}


void Report::organiseDataForEeprom(){ //invert the data if directed left
    if (directedLeft){
        char pathDataTemp[4];
        for(uint8_t i = 0; i < 4; i++){
        pathDataTemp[i] = pathData[i];
        }

        for(uint8_t i = 0; i < 4; i++){
            pathData[i] = pathDataTemp[3 - i];
        }
    }
}


void Report::createEepromReadyData(){
    if (Robot::symbolVisitedCounter == 2){
        pathData[0] = 2;
        pathData[1] = 1;
        pathData[2] = static_cast<uint8_t>(Robot::betweenSymbols[0]);
        pathData[3] = static_cast<uint8_t>(Robot::betweenSymbols[1]);
    }
    else if(Robot::symbolVisitedCounter == 3){
        pathData[0] = 1;
        pathData[1] = static_cast<uint8_t>(Robot::betweenSymbols[0]);
        pathData[2] = static_cast<uint8_t>(Robot::betweenSymbols[1]);
        pathData[3] = static_cast<uint8_t>(Robot::betweenSymbols[2]);
    }
    organiseDataForEeprom();
}



const char* Report::dataToString(uint8_t data, bool rightSide){
    switch (data){
        case 1: 
            if (rightSide)
                return "<<<";
            else    
                return ">>>";
            break;

        case 2:
            return "---";
            break;
        case 3:
            return "(O)";
            break;
        default:
            return "???";
            break;
    }
}


void Report::spaceForFormatting(uint8_t& reportLineIndex)
{
    report[reportLineIndex++] = NEWLINE;
    report[reportLineIndex++] = NEWLINE;
    report[reportLineIndex++] = NEWLINE;
}

void Report::createReport(){
    uint8_t reportLineIndex = 0;
    uint8_t data[12];
    Memoire24CXXX memory;
    memory.lecture(0, data, 12);
    report[reportLineIndex++] =  NEWLINE;
    report[reportLineIndex++] = "robot   : GoByte\n";
    report[reportLineIndex++] = "equipe  : 3242";

    spaceForFormatting(reportLineIndex);

    report[reportLineIndex++] = "            ________                                                                        \n";
    report[reportLineIndex++] = "          | |      | |                      \\_                          |  __                    \n";
    report[reportLineIndex++] = "          | |      | |                        \\_                        | /  |                   \n";


    report[reportLineIndex++] = dataToString(data[0]);
    report[reportLineIndex++] = "-------| |      | |---------";
    report[reportLineIndex++] = dataToString(data[1]);
    report[reportLineIndex++] = "---------     \\----------";
    report[reportLineIndex++] = dataToString(data[2], true);
    report[reportLineIndex++] = "----------|{   |----------------";
    report[reportLineIndex++] = dataToString(data[3], true);
    report[reportLineIndex++] = NEWLINE;

    report[reportLineIndex++] = "          | |      | |                                                  | \\__|                   \n"; 
    report[reportLineIndex++] = "          | |______| |                                                  |                        \n";

    spaceForFormatting(reportLineIndex);

    report[reportLineIndex++] = "                                                                           ________               \n";
    report[reportLineIndex++] = "            _______                            __  |                     | |      | |             \n";
    report[reportLineIndex++] = "           /       \\                          |  \\ |                     | |      | |             \n";
   

    report[reportLineIndex++] = dataToString(data[4]);
    report[reportLineIndex++] = "-------(         )----------";
    report[reportLineIndex++] = dataToString(data[5]);
    report[reportLineIndex++] = "------------|   }|----------";
    report[reportLineIndex++] = dataToString(data[6], true);
    report[reportLineIndex++] = "--------| |      | |---------";
    report[reportLineIndex++] = dataToString(data[7], true);
    report[reportLineIndex++] = NEWLINE;

    report[reportLineIndex++] = "           \\_______/                          |__/ |                     | |      | |             \n";
    report[reportLineIndex++] = "                                                   |                     | |______| |             \n";

    spaceForFormatting(reportLineIndex);

    report[reportLineIndex++] = "            ________                                                                           \n";
    report[reportLineIndex++] = "          | |      | |                    ______                        _/                  \n";
    report[reportLineIndex++] = "          | |      | |                   /      \\                     _/                     \n";
    
    
    
    report[reportLineIndex++] = dataToString(data[8]);
    report[reportLineIndex++] = "-------| |      | |---------";
    report[reportLineIndex++] = dataToString(data[9]);
    report[reportLineIndex++] = "------(        )--------";
    report[reportLineIndex++] = dataToString(data[10], true);
    report[reportLineIndex++] = "--------/      ------------------";
    report[reportLineIndex++] = dataToString(data[11], true);
    report[reportLineIndex++] = NEWLINE;
    

    report[reportLineIndex++] = "          | |      | |                   \\______/                                             \n";
    report[reportLineIndex++] = "          | |______| |                                                                         \n";
}

void Report::sendReportViaUART(){
    createReport();
    for (uint8_t i = 0; i < 52; i++){ 
        SerialCommunication::readViaUART(report[i]); 
    }
}