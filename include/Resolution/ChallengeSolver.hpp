#pragma once

#include "ROBUSMovement.hpp"
#include "Colour_Sensor/Color_Detector.hpp"
#include "Distance_sensor/GP2D12.hpp"
#include "Line_Follower/Line_follower.hpp"
#include "CupWhacker.hpp"
#include "Cup_Placer/CupPlacer.hpp"

#define ZONE2_DISTANCE_CM 61.96f
#define ZONE4_5_DISTANCE_CM 243.84f
#define ZONE9_0_DISTANCE_CM ZONE4_5_DISTANCE_CM

#define ZONE4_DISTANCE_CM 121.92f

#define ZONE6_MEET_DISTANCE_CM 15.0f

#define ROBOT_RSIDE_GREEN_TO_WALL_DISTANCE_CM (60.96f - DISTANCE_BT_WHEEL) / 2

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

void ChallengeSolver_TotallyFollowingTheLine();
void ChallengeSolver_dropCupTime();

void ChallengerSolver_ExecuteRace();

void waitForBumper();

