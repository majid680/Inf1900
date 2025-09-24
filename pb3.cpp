#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void ajustementPWM (int duree) {
    OCR1A = duree;
    OCR1B = duree;
    TCCR1A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM10);
    TCCR1B = (1<<CS01) ;
    TCCR1C = 0;
}

int main(){
    DDRD |= (1<<PD4)|(1<<PD3);
    DDRD |= (1<<PD5);
    DDRA |= (1<<PD2);
    int valeurActivationPWM[5] = {0,64,128,191,255};
    for(int i=0;i<5;i++){
        ajustementPWM (valeurActivationPWM[i]);
        _delay_ms(2000);
    }  
    return 0;
}
