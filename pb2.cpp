#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t gMinuterieExpiree;
volatile uint8_t gBoutonPoussoir; 


void allumerRouge()
{
    PORTA |= 1 << PA0;
    PORTA &= ~(1<< PA1);
}
void allumerVert()
{
    PORTA |= 1 << PA1;
    PORTA &= ~(1<< PA0);
}
void clignoterRouge()
{
    for (i=0; i<10; i++)
    {
        rouge();
        _delay_ms(100);
        eteint();
        _delay_ms(900);
    }
}


void eteint()
{
    PORTA &= ~(1<< PA0);
    PORTA &= ~(1<< PA1);
}

ISR (TIMER1_COMPA_vect) 
{
    _delay_ms(30);
    gMinuterieExpiree = 1;
    EIFR |= (1 << INTF0) ;
}


ISR (INT0_vect) 
{
    _delay_ms(30);
    gBoutonPoussoir = 1;
    EIFR |= (1 << INTF0) ;
}

int main()
{
    cli();
    DDRA |= (1 << PA0) |(1 << PA1);
    DDRD &= ~(1 << PD2);
    EIMSK |= (1 << INT0) ;
    EICRA |= (1 << ISC01) | (1 << ISC00) ; 
    sei();

    clignoterRouge();
    do {
        allumerVert();
    } while ( gMinuterieExpiree == 0 && gBoutonPoussoir == 1);
    do {
        allumerRouge();
    } while ( gMinuterieExpiree == 1);

    cli ();

    // Verifier la réponse
    'modifier ici'

    return 0;
}