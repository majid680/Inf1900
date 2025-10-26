#pragma once
#include <avr/io.h>
#include "1900util.h"

enum class ValuePrescaler : uint16_t {div1 = 1, div8 = 8, div64 = 64, div256 = 256, div1024 = 1024};

class Timer1{
    private:
    static uint32_t timerCounter;
    static ValuePrescaler prescaler;
    static const  uint16_t maxTimeForPrescaler8 = 65;      // 65 536 (max value of OCR1A) / (F_CPU / 8) * 1000 = 65
    static const  uint16_t maxTimeForPrescaler64 = 524;    // 65 536 (max value of OCR1A) / (F_CPU / 64) * 1000 = 524
    static const  uint16_t maxTimeForPrescaler256 = 2097;  // 65 536 (max value of OCR1A) / (F_CPU / 256) * 1000 = 2097
    static void setPrescaler(ValuePrescaler prescaler);
    static void findPrescaler(uint16_t time);
    

    public: 
    static void startCounter(uint16_t time);//time (ms) between each interrupt call
    static void stopTimer();
    static void resumeTimer();
    static void resetTimerCounter();
    static uint32_t getTimerCounter();
    static void incTimerCounter();

    
};

