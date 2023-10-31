#pragma once

#include "ROBUSMovement.hpp"

typedef struct
{
    float positionX_pulses;
    float positionY_pulses;
} RobotPosition;

typedef struct 
{
    RobotPosition wantedPosition;
    float wantedOrientation;
} ChallengeStep;

void GetRobotOrientation(RobotPosition position);

void ChallengeSolver_Init();

void ChallengeSolver_ExecuteAllSteps();
void ChallengeSolver_ExecuteFirstLap();
void ChallengeSolver_ExecuteSecondLap();

void ChallengerSolver_ExecuteRace();

