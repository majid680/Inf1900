#define F_CPU 8000000UL
#include <avr/io.h>
#include "memoire_24.h"
#include <stdlib.h>
#include <stdio.h>
#include <rs232.h>

void SerialCommunication::initialisationUART() {
    UBRR0H = 0;
    UBRR0L = 0xCF;
    
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void SerialCommunication::transmissionUART(uint8_t donnee) {

    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = donnee;
}

void SerialCommunication::readFlash(const char* display)
{

    for (uint8_t i = 0; display[i] != '\0'; i++) {
        transmissionUART(display[i]);
    }
    transmissionUART('\n');
}

void SerialCommunication::readFlash(uint16_t display)
{
    char buffer[maxSizeBuffer];
    utoa(display, buffer, base10); 

    for (uint8_t i = 0; buffer[i] != '\0'; i++) {
        transmissionUART(buffer[i]);
    }

    transmissionUART('\n');
}

