#define F_CPU 8000000UL
#include <avr/io.h>
#include "memoire_24.h"
#include <stdlib.h>
#include <rs232.h>

const uint8_t NEWLINE  = '\n';

void SerialCommunication::initializationUART() {
    UBRR0H = 0;
    UBRR0L = BAUD;
    
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void SerialCommunication::transmissionUART(uint8_t value) {

    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = value;
}

void SerialCommunication::readViaUART(const char* display)
{
    for (uint8_t i = 0; display[i] != '\0'; i++) {
        transmissionUART(display[i]);
    }
}

void SerialCommunication::readViaUART(uint16_t display)
{
    char buffer[MAX_SIZE_BUFFER];
    utoa(display, buffer, BASE_10); 

    for (uint8_t i = 0; buffer[i] != '\0'; i++) {
        transmissionUART(buffer[i]);
    }

    transmissionUART(NEWLINE);
}

void SerialCommunication::readViaUART(const char* display, uint8_t size)
{

    for (uint8_t i = 0; i < size; i++) {
        transmissionUART(display[i]);
    }
}


uint8_t SerialCommunication::receiveUART() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;                   
}