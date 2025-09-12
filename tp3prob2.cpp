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
int main()
{
    DDRB |= (1 << PB0) | (1 << PB1);
    uint16_t repetitonDePeriode60Hz = 120;
    double tempsEleve60Hz= 0;
    double tempsBas60Hz = 16.666666666667;
    double variationTempsEtatHaut60Hz = 4.25;
    bool MarcheEnAvant60Hz = true;
    etapesControleRoueRobot(repetitonDePeriode60Hz, tempsEleve60Hz, tempsBas60Hz, variationTempsEtatHaut60Hz, MarcheEnAvant60Hz);

    uint16_t repetitonDePeriode400Hz = 800;
    double tempsEleve400Hz= 0;
    double tempsBas400Hz = 2.5;
    double variationTempsEtatHaut400Hz = 0.625;
    bool MarcheEnAvant400Hz = false;
    etapesControleRoueRobot(repetitonDePeriode400Hz, tempsEleve400Hz, tempsBas400Hz, variationTempsEtatHaut400Hz, MarcheEnAvant400Hz);
    
    return 0;
}



