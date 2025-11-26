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
    public: 
        static void startCounter(uint16_t time); //time (ms) between each interrupt call
        static void stopTimer();
        static void resumeTimer();
        static void resetTimerCounter();
        static uint32_t getTimerCounter();
        static void incTimerCounter();

    private:
        static volatile uint32_t timerCounter;
        static ValuePrescaler prescaler;
        
        static const uint16_t MAX_OCR1A = 65535;
        static const uint16_t SECOND_IN_MS = 1000;

        static const  uint8_t MAX_TIME_PRESCALER8 = 65;      // 65 536 (max value of OCR1A) / (F_CPU / 8) * 1000 = 65
        static const  uint16_t MAX_TIME_PRESCALER64 = 524;    // 65 536 (max value of OCR1A) / (F_CPU / 64) * 1000 = 524
        static const  uint16_t MAX_TIME_PRESCALER256 = 2097;  // 65 536 (max value of OCR1A) / (F_CPU / 256) * 1000 = 2097


        Timer1() = delete;
        
        static void setPrescaler(ValuePrescaler prescaler);
        static void findPrescaler(uint16_t time);
};

// intented use for sound generation, frequency can go from 4 MHz to approx 15 Hz
// Output on OC0A (PB3) and other pin on PB5
class Timer0{
    public:
        static void initializationTimer(); 
        static void setFrequency(uint32_t frequency);
        static void stopTimer();
        static void resumeTimer();    
    
    private:
        static ValuePrescaler prescaler;
        
        static const uint16_t MAX_OCR0A = 255;

        static const  uint16_t MIN_FREQ_PRESCALER1 = 15625;      // F_CPU / (2 * 1 * 256)= 15 625 Hz
        static const  uint16_t MIN_FREQ_PRESCALER8 = 1953;      // F_CPU / (2 * 8 * 256)= 1953 Hz
        static const  uint8_t MIN_FREQ_PRESCALER64 = 244;    // F_CPU / (2 * 64 * 256)= 244 Hz
        static const  uint8_t MIN_FREQ_PRESCALER256 = 61;  // F_CPU / (2 * 256 * 256)= 61 Hz
        static const uint8_t CYCLE_PER_PERIOD = 2;

        Timer0() = delete;

        static void setPrescaler(ValuePrescaler prescaler);
        static void findPrescaler(uint32_t frequency);
};