
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


constexpr uint8_t BROCHE_ENTREE_INTERRUPTEUR = PD2;
constexpr uint8_t BROCHE_POSITIVE_DEL = PB0;
constexpr uint8_t BROCHE_NEGATIVE_DEL = PB1;


constexpr uint8_t DELAI_REBONDISSEMENT_INTERRUPTEUR_MS = 10;
constexpr uint8_t DELAI_ALTERNATION_ROUGE_VERT_MS = 2;


enum class ETAT {INIT, PREMIER_APPUI, PREMIERE_RELACHE, DEUXIEME_APPUI, DEUXIEME_RELACHE, TROISIEME_APPUI, TROISIEME_RELACHE};

volatile ETAT etatPresent;


ISR (INT0_vect ) {
    // laisser un délai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms ( 30 );
    // se souvenir ici si le bouton est pressé ou relâché
    // changements d'état tels que ceux de la semaine précédente
    switch (etatPresent)
        {
            case ETAT::INIT:
                etatPresent = ETAT::PREMIER_APPUI;
                break;

            case ETAT::PREMIER_APPUI:
                etatPresent = ETAT::PREMIERE_RELACHE;
                break;

            case ETAT::PREMIERE_RELACHE:
                etatPresent = ETAT::DEUXIEME_APPUI;
                break;

            case ETAT::DEUXIEME_APPUI:
                etatPresent = ETAT::DEUXIEME_RELACHE;
                break;

            case ETAT::DEUXIEME_RELACHE:
                etatPresent = ETAT::TROISIEME_APPUI;
                break;

            case ETAT::TROISIEME_APPUI:
                etatPresent = ETAT::TROISIEME_RELACHE;
                break;

            case ETAT::TROISIEME_RELACHE:
                etatPresent = ETAT::INIT;
                break;
        }
    EIFR |= (1 << INTF0) ;
}


void eteindreDel()
{
    PORTB &= ~((1 << BROCHE_POSITIVE_DEL) | (1 << BROCHE_NEGATIVE_DEL)); 
}

void allumerVert()
{
    PORTB |= (1 << BROCHE_POSITIVE_DEL);
    PORTB &= ~(1 << BROCHE_NEGATIVE_DEL); 
}
void allumerRouge()
{
    PORTB |= (1 << BROCHE_NEGATIVE_DEL);
    PORTB &= ~(1 << BROCHE_POSITIVE_DEL); 
}
void allumerAmbre()
{
    allumerRouge();
    _delay_ms(DELAI_ALTERNATION_ROUGE_VERT_MS);
    allumerVert();
    _delay_ms(DELAI_ALTERNATION_ROUGE_VERT_MS);
}


int main()
{
    cli();

    DDRD &= ~(1 << BROCHE_ENTREE_INTERRUPTEUR); 
    DDRB |= ((1 << BROCHE_POSITIVE_DEL) | (1 << BROCHE_NEGATIVE_DEL)); 

    EIMSK |= (1 << INT0) ;
    EICRA |= (1 << ISC00) ;
    etatPresent = ETAT::INIT;
    sei ();
    

    while (true)
    {
        
        switch (etatPresent)
        {
            case ETAT::INIT:
                allumerRouge();
                break;

            case ETAT::PREMIER_APPUI:
                allumerAmbre();
                break;

            case ETAT::PREMIERE_RELACHE:
                allumerVert();
                break;

            case ETAT::DEUXIEME_APPUI:
                allumerRouge();
                break;

            case ETAT::DEUXIEME_RELACHE:
                eteindreDel();
                break;

            case ETAT::TROISIEME_APPUI:
                allumerVert();
                break;

            case ETAT::TROISIEME_RELACHE:
                break;
        }
        
    }
    return 0;
}