#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void rouge()
{
    PORTA |= 1 << PA0;
    PORTA &= ~(1<< PA1);
}

void vert()
{
    PORTA |= 1 << PA1;
    PORTA &= ~(1<< PA0);
}

void eteint()
{
    PORTA &= ~(1<< PA0);
    PORTA &= ~(1<< PA1);
}
void dynamic_delay(double temps)
{
    for(int i=0; i<temps; i++)
    {
        _delay_ms(1);
    }
}


int main()
{
    DDRA |= (1 << PA0) | (1 << PA1);
    double dureeOn= 30;
    double dureeOff = 0;
    double variationMsRouge = 0.4;
    
    for (int i=0; i<100; i++)
    {
        rouge();
        dureeOn -=variationMsRouge;
        dynamic_delay(dureeOn);
        eteint();
        dureeOff +=variationMsRouge;
        dynamic_delay(dureeOff);
    }

    _delay_ms(1000);

    double dureeOnVert= 30;
    double dureeOffVert = 0;    
    double variationMsVert = 0.4;
    for (int i=0; i<100; i++)
    {
        vert();
        dureeOnVert -=variationMsVert;
        dynamic_delay(dureeOnVert);
        eteint();
        dureeOffVert +=variationMsVert;
        dynamic_delay(dureeOffVert);
    }
    return 0;
}
