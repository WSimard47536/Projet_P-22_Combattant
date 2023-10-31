#include "Cup_Placer/CupPlacer.hpp"

void CupPlacer_Init()
{
    S3003_Init(SERVO_CUP_PLACER);
    S3003_SetAngle(SERVO_CUP_PLACER, SERVO_MIN_ANGLE);
}

void CupPlacer_PlaceCup()
{
    CupPlacer_Init();
    // Tirer le fil ---> rotation de 180
    S3003_SetAngle(SERVO_CUP_PLACER, SERVO_MAX_ANGLE);
}

void CupPlacer_Reset()
{
    S3003_setDefault(SERVO_CUP_PLACER);
}