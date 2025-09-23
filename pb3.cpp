#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


constexpr uint8_t nbEtapesPourFrequenceDonnee = 5;

void delaiDynamique(double temps)
{
    for(uint8_t i=0; i<temps; i++)
    {
        _delay_ms(1);
    }
}


void tournerRoue(double& dureeOn, bool directionRoue)
{
    if (dureeOn >0)
    {
        if (directionRoue == true)
        {    
            PORTB |= (1 << PB0);
            PORTB |= (1 << PB1);
        }
        else
        {
            PORTB |= (1 << PB0);
            PORTB &= ~(1 << PB1);
        }
    }
}

void changerDuree(double& dureeOn, double& dureeOff, double variation)
{
    dureeOn += variation;
    dureeOff -= variation;
}

void eteint()
{
    PORTB &= ~(1<< PB0);
    PORTB &= ~(1<< PB1);
}

void etapesControleRoueRobot(uint16_t repetitonDePeriode, double tempsEleve, double tempsBas, double variation, bool directionRoue)
{
    for (uint8_t i=0; i < nbEtapesPourFrequenceDonnee; i++)
    {
        for (uint16_t j=0; j < repetitonDePeriode; j++)
        {
            tournerRoue(tempsEleve, directionRoue);
            delaiDynamique(tempsEleve);
            eteint();
            delaiDynamique(tempsBas);
        }

        changerDuree(tempsEleve, tempsBas, variation);
    } 
}


void ajustementPwm ( uint16_t duree) {

    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5

    // page 130 de la description technique du ATmega324PA)

    OCR1A = duree ;

    OCR1B = duree ;


    // division d'horloge par 8 - implique une fréquence de PWM fixe

    TCCR1A =0;

    TCCR1B |= (1 << CS02);

    TCCR1C = 0;

}

int main()
{
    
    
    return 0;
}



