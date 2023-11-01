#include "Cup_Placer/CupPlacer.hpp"
#include "ROBUSMovement.hpp"

void CupPlacer_Init()
{
    S3003_Init(SERVO_CUP_PLACER);
    S3003_SetAngle(SERVO_CUP_PLACER, SERVO_MAX_ANGLE / 2);
}

void CupPlacer_PlaceCup()
{
    CupPlacer_Init();
    // Tirer le fil ---> rotation de 180
    S3003_SetAngle(SERVO_CUP_PLACER, SERVO_MAX_ANGLE);
    delay(500);
    CupPlacer_Reset();
    CupPlacer_SkipCup();
}

void CupPlacer_Reset()
{
    S3003_setDefault(SERVO_CUP_PLACER);
}

void CupPlacer_SkipCup()
{
    // Reculer 20 cm
    ROBUSMovement_arcMove_global(COLOR_GREEN, 0, BACKWARD, 1, 20);
    ROBUSMovement_EmergencyStop();

    // Turn right
    ROBUSMovement_turnOnSelf_cedric(RIGHT_TURN, 0.20, 90); // à revoir

    // Move straight pour 20 cm
    ROBUSMovement_arcMove_global(COLOR_GREEN, 0, FORWARD, 1, 20);
    ROBUSMovement_EmergencyStop();

    // Turn left
    ROBUSMovement_turnOnSelf_cedric(LEFT_TURN, 0.20, 90);

    // Move straight
    ROBUSMovement_arcMove_global(COLOR_GREEN, 0, FORWARD, 1, 20);
    ROBUSMovement_EmergencyStop();
}