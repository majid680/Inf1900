#pragma once
#include <avr/io.h>

enum class Direction{forward, backward};

enum class InterruptMode{risingEdge, fallingEdge, anyEdge, lowLevel};

enum class ButtonInterruptType{int0, int1, int2};

class Initialization{

    public:
    Initialization() = delete;
    
    static void setInput(volatile uint8_t* port, uint8_t pin);
    static void setOutput(volatile uint8_t* port, uint8_t pin);
    static void setOutput(volatile uint8_t* port, uint8_t pin1, uint8_t pin2);

};

class Delay{
    private:
   
    const static uint8_t delay = 1;
   
    public:
    Delay() = delete;
    static void dynamicDelay(uint16_t time); //in milliseconds (can wait a max of approx. 65 seconds)

};