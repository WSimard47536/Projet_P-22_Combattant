
#include "Proximity_sensors/InfraRed.hpp"
#include "Proximity_sensors/DC2318.hpp"

void beep(unsigned count)
{
    for (size_t i = 0; i < count; i++)
    {
        AX_BuzzerON();
        delay(100);
        AX_BuzzerOFF();
        delay(100);
    }
    delay(400);
}

void DC2318_Init(unsigned leftPin, unsigned rightPin)
{
    IR_Init(leftPin);
    IR_Init(rightPin);
}

/*
    On considere ici que la balle est presente sauf si les deux LED's sont alumees
    Ailleurs, il y a deux cas possible (les deux peuvent cependant representer un cas de faux negatif, mais on on a qu'a a appliquer l'algorithm de l'ostrich):
    1- Soit la LED rouge ou verte est alummee, mais pas les deux
    2- Soit aucune des LED's est alumee
*/
bool DC2318_Read(unsigned leftPin, unsigned rightPin)
{
    if (IR_Read(leftPin) && IR_Read(rightPin))
    {
        beep(1);
        return true;
    }
    else
        return false;
}
