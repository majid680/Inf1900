#define F_CPU 8000000UL
#include <avr/io.h>
#include "memoire_24.h"
#include "eeprom.h"
#include "delay.h"
#include "rs232.h"



Memoire24CXXX Eeprom::memory = Memoire24CXXX();


void Eeprom::writeData(uint16_t address, const char* data, uint8_t size)
{       
    memory.ecriture(address, (uint8_t*) data, size);
}

char* Eeprom::extractFromEeprom(uint16_t address, char* extractedData, uint8_t size)
{
    memory.lecture(address,(uint8_t*) extractedData, size); 

    return extractedData;
}

uint8_t Eeprom::findLength(const char* data) {
    uint8_t length = 0;
    while (data[length] != END_OF_STRING) {    
        length++;
    }
    return length;
}


uint8_t Eeprom::writeFromSerial(uint16_t startAddress) {
    uint8_t byteReceived = SerialCommunication::receiveUART();
    memory.ecriture(startAddress, &byteReceived, NB_OF_BYTE);     
    
    return byteReceived;
}

void Eeprom::writeProgram(){
    SerialCommunication::initializationUART();
    
    writeFromSerial(FILE_SIZE_ADDR); 
    writeFromSerial(FILE_SIZE_ADDR + INCREMENT_ADDR);  

    uint16_t fileSize = getFileSize();

    for (uint16_t currentAddress = STARTING_ADDR; currentAddress < fileSize; currentAddress++)
    {
        writeFromSerial(currentAddress);
    }
}

uint16_t Eeprom::getFileSize(){
    char extractedData[INSTRUCTION_BYTE];
    Eeprom::extractFromEeprom(FILE_SIZE_ADDR, extractedData, INSTRUCTION_BYTE); 

    uint16_t fileSize = (extractedData[0] << SHIFT_LEFT) | extractedData[1]; 

    return fileSize;
}