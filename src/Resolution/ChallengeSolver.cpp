#include "Resolution/ChallengeSolver.hpp"

RobotPosition currentRobotPosition;
int assignedColor;

void ChallengeSolver_Init()
{
    currentRobotPosition.positionX_pulses = 0; //START POSITION_x
    assignedColor = Color_Detection();
}

/*float GetRobotOrientation()
{
    // Faire arctan pour avoir en degrés
    //return (position.positionX_pulses % FULL_ROTATIONS_PULSES) / (position.positionY_pulses % FULL_ROTATIONS_PULSES);
}*/

void ChallengeSolver_ExecuteAllSteps()
{

}

void ChallengeSolver_ExecuteFirstLap()
{
    // Turn Right (zone 1)
    ROBUSMovement_arcMove(0.25f, assignedColor, 90, RIGHT_TURN);

    // Straight (zone 2)
    ROBUSMovement_moveStraight(FORWARD, 0.25f, ZONE2_DISTANCE_CM);

    // Turn Right (zone 3)
    ROBUSMovement_arcMove(0.25f, assignedColor, 90, RIGHT_TURN);

    // Move Straight and Whack the cup (zone 4 - 5)
    ROBUSMovement_moveStraight(FORWARD, 0.25f, ZONE4_5_DISTANCE_CM); // MESURER LA DISTANCE SUR LE PARCOURS

    // Turn to create intersection point with black line (zone 6)
    if (assignedColor == GREEN)
    {
        ROBUSMovement_turnOnSelf(LEFT_TURN, 0.25f, 25.0f);
    }
    else 
    {
        ROBUSMovement_turnOnSelf(RIGHT_TURN, 0.25f, 25.0f);
    }

    // Go forward until center line follower detects line (zone 6)
    ROBUSMovement_moveStraight(FORWARD, 0.25f, ZONE6_MEET_DISTANCE_CM);

    // Follow line until ball is found (zone 6 - 7 - 8)
    // SUIVRE LA LIGNE
    // Drop cup on ball
    // DROP LE CUP

    // Go to zone 9 (zone 6 - 7 - 8)
    // Continuer de suivre la ligne jusqu'à la fin

    // Go to start with jump (zone 9 - 0)
    float speedFactor = 0.95f;
    MOTOR_SetSpeed(LEFT_MOTOR, 0.40f);
    MOTOR_SetSpeed(RIGHT_MOTOR, 0.40f);
    
    while (ENCODER_Read(RIGHT_MOTOR) < ZONE9_0_DISTANCE_CM)
    {
        float currentDistanceToWall = GP2D12_Read(3);
        if (currentDistanceToWall > ROBOT_RSIDE_GREEN_TO_WALL_DISTANCE_CM)
        {
            MOTOR_SetSpeed(LEFT_MOTOR,0.40f / speedFactor);
        }
        else if (currentDistanceToWall < ROBOT_RSIDE_GREEN_TO_WALL_DISTANCE_CM)
        {
            MOTOR_SetSpeed(LEFT_MOTOR,0.40f * speedFactor);
        }
        if (LineFollower_Read(PA_LINEFOLLOWER) != ERROR)
        {
            break;
        }
    }
    ROBUSMovement_stop();
}

void ChallengeSolver_ExecuteSecondLap()
{
    // Turn Right (zone 1)
    ROBUSMovement_arcMove(0.25f, GREEN, 90, RIGHT_TURN);

    // Straight (zone 2)
    ROBUSMovement_moveStraight(FORWARD, 0.40f, ZONE2_DISTANCE_CM);

    // Turn Right (zone 3)
    ROBUSMovement_arcMove(0.25f, GREEN, 90, RIGHT_TURN);

    // Straight (zone 4 - 5)
    ROBUSMovement_moveStraight(FORWARD, 0.40f, ZONE4_DISTANCE_CM);

    // Turn Right (zone 6)
    ROBUSMovement_arcMove(0.25f, BLUE, 90, RIGHT_TURN);

    // Straight (zone 6 - 9)
    float speedFactor = 0.95f;
    MOTOR_SetSpeed(LEFT_MOTOR,0.40f);
    MOTOR_SetSpeed(RIGHT_MOTOR,0.40f);
    
    while (ENCODER_Read(RIGHT_MOTOR) < ZONE9_0_DISTANCE_CM + 15.0f)
    {
        float currentDistanceToWall = GP2D12_Read(3);
        if (currentDistanceToWall > ROBOT_RSIDE_GREEN_TO_WALL_DISTANCE_CM)
        {
            MOTOR_SetSpeed(LEFT_MOTOR,0.40f / speedFactor);
        }
        else if (currentDistanceToWall < ROBOT_RSIDE_GREEN_TO_WALL_DISTANCE_CM)
        {
            MOTOR_SetSpeed(LEFT_MOTOR,0.40f * speedFactor);
        }
    }
    ROBUSMovement_stop();
}

void ChallengerSolver_ExecuteRace()
{
    
}