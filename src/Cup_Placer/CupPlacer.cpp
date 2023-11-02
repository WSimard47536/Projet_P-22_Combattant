#include "Cup_Placer/CupPlacer.hpp"
#include "ROBUSMovement.hpp"

void CupPlacer_Init()
{
    S3003_Init(SERVO_CUP_PLACER);
    S3003_SetAngle(SERVO_CUP_PLACER, SERVO_MAX_ANGLE / 2);
}

void CupPlacer_PlaceCup()
{
    // Tirer le fil ---> rotation de 180
    S3003_SetAngle(SERVO_CUP_PLACER, SERVO_MAX_ANGLE);
}

void CupPlacer_Reset()
{
    S3003_setDefault(SERVO_CUP_PLACER);
}

void CupPlacer_TurnAroundCup(){
    ROBUSMovement_arcMove_straight(BACKWARD, 21.55);
    ROBUSMovement_arcMove_straight(3, ROBUSMovement_turn_math(37));
    ROBUSMovement_EmergencyStop();
}