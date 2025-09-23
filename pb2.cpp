#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t gMinuterieExpiree;
volatile uint8_t gBoutonPoussoir; 
constexpr int DUREE = 7812;

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

void eteint()
{
    PORTA &= ~(1<< PA0);
    PORTA &= ~(1<< PA1);
}
void clignoterRouge()
{
    for (int i=0; i<10; i++)
    {
        allumerRouge();
        _delay_ms(100);
        eteint();
        _delay_ms(900);
    }
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


void partirMinuterie ( uint16_t duree ) {
    gMinuterieExpiree = 0;
    TCNT1 = 0;
    OCR1A = DUREE;
    TCCR1A = 0 ;
    TCCR1B |= (1 << CS02) | (1 << CS00);
    TCCR1C = 0;
    TIMSK1 |= (1 << ICIE1 );
}

int main()
{
    cli();
    DDRA |= (1 << PA0) |(1 << PA1);
    DDRD &= ~(1 << PD2);
    EIMSK |= (1 << INT0) ;
    EICRA |= (1 << ISC01) | (1 << ISC00) ; 
    

    clignoterRouge();
    sei();
    
    partirMinuterie(DUREE);
    do {
        allumerVert();
    } while ( gMinuterieExpiree == 0 && gBoutonPoussoir == 1);
    do {
        allumerRouge();
    } while ( gMinuterieExpiree == 1);

    cli ();
    

    return 0;
}