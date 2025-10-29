#define F_CPU 8000000UL
#include <avr/io.h>
#include "memoire_24.h"
#include "writeEeprom.h"
#include "delay.h"

writeEeprom::writeEeprom()
{
    memory = Memoire24CXXX();
}

void writeEeprom::writeData(uint16_t address, const char* data, uint8_t size)
{
    memory.ecriture(address, (uint8_t*) data, size);
}

bool writeEeprom::compareData(uint16_t address, const char* data, uint8_t size)
{
    memory.lecture(address,(uint8_t*) extractedData, size);
    Delay::dynamicDelay(5); 
    isIdentical = true;
    for (int comparedChar =0; comparedChar < size; comparedChar++){
        if (extractedData[comparedChar] != data[comparedChar]) {
            isIdentical = false;
            break;
        }          
    }
    return isIdentical;
}