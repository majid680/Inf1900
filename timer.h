/*################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#                 timer class                    #
#                                                #
#                                                #
################################################*/

#pragma once
#include <avr/io.h>

enum class ValuePrescaler : uint16_t {div1 = 1, div8 = 8, div64 = 64, div256 = 256, div1024 = 1024};

class Timer1{
    private:
    static uint32_t timerCounter;
    static const uint16_t maxOCR1A = 65535;
    static const uint16_t secondInMs = 1000;
    static ValuePrescaler prescaler;
    static const  uint8_t maxTimeForPrescaler8 = 65;      // 65 536 (max value of OCR1A) / (F_CPU / 8) * 1000 = 65
    static const  uint16_t maxTimeForPrescaler64 = 524;    // 65 536 (max value of OCR1A) / (F_CPU / 64) * 1000 = 524
    static const  uint16_t maxTimeForPrescaler256 = 2097;  // 65 536 (max value of OCR1A) / (F_CPU / 256) * 1000 = 2097

    Timer1() = delete;
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



// intented use for sound generation, frequency can go from 4 MHz to approx 15 Hz
// Output on OC0A (PB3)
class Timer0{
    private:
    static const uint16_t maxOCR0A = 255;
    static const  uint16_t minFrequencyForPrescaler1 = 15625;      // F_CPU / (2 * 1 * 256)= 15 625 Hz
    static const  uint16_t minFrequencyForPrescaler8 = 1953;      // F_CPU / (2 * 8 * 256)= 1953 Hz
    static const  uint8_t minFrequencyForPrescaler64 = 244;    // F_CPU / (2 * 64 * 256)= 244 Hz
    static const  uint8_t minFrequencyForPrescaler256 = 61;  // F_CPU / (2 * 256 * 256)= 61 Hz
    static const uint8_t cyclePerPeriod = 2;
    static ValuePrescaler prescaler;

    Timer0() = delete;
    static void setPrescaler(ValuePrescaler prescaler);
    static void findPrescaler(uint32_t frequency);

    public:

    static void startTimer(uint32_t frequency); //sets the prescaler for timer0
    static void changeFrequency(uint32_t frequency);
    static void stopTimer();
    static void resumeTimer();

};