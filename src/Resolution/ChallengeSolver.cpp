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
    ROBUSMovement_arcMove_turn(assignedColor, FORWARD, RIGHT_TURN, 90.0);

    // Straight (zone 2)
    ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_2_FT);

    // Turn Right (zone 3)
    ROBUSMovement_arcMove_turn(assignedColor, FORWARD, RIGHT_TURN, 90.0);

    // Move Straight and Whack the cup (zone 4 - 5)
    ROBUSMovement_continuousPID_begin_cm(STRAIGHT_8_FT);
    while(ROBUSMovement_stopRequirementContinuous()){
        ROBUSMovement_momentaryPID_inwhile();
        CupWhacker_main();
    }
    ROBUSMovement_EmergencyStop();

    //METTRE CODE POUR "SUIVEUR DE LIGNE"

    

    /*ROBUSMovement_moveStraight(FORWARD, 0.25f, ZONE4_5_DISTANCE_CM); // MESURER LA DISTANCE SUR LE PARCOURS

    // Turn to create intersection point with black line (zone 6)
    if (assignedColor == GREEN)
    {
        ROBUSMovement_turnOnSelf(LEFT_TURN, 0.25f, 25.0f);
    }
    else 
    {
        ROBUSMovement_turnOnSelf(RIGHT_TURN, 0.25f, 25.0f);
    }*/

    // Go forward until center line follower detects line (zone 6)
    //ROBUSMovement_moveStraight(FORWARD, 0.25f, ZONE6_MEET_DISTANCE_CM);

    // Follow line until ball is found (zone 6 - 7 - 8)
    // SUIVRE LA LIGNE
    // Drop cup on ball
    // DROP LE CUP

    // Go to zone 9 (zone 6 - 7 - 8)
    // Continuer de suivre la ligne jusqu'à la fin

    // Go to start with jump (zone 9 - 0)
    
    /*float speedFactor = 0.95f;
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
    }*/
    //ROBUSMovement_stop();
    ROBUSMovement_arcMove_straight(FORWARD, 259.08); // 8 pieds et demi
}

void ChallengeSolver_ExecuteSecondLap()
{
    // Turn Right (zone 1)
    ROBUSMovement_arcMove_turn(COLOR_GREEN, FORWARD, RIGHT_TURN, 90.0);

    // Straight (zone 2)
    ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_2_FT);

    // Turn Right (zone 3)
    ROBUSMovement_arcMove_turn(COLOR_GREEN, FORWARD, RIGHT_TURN, 90.0);

    // Straight (zone 4 - 5)
    ROBUSMovement_arcMove_straight(FORWARD, ZONE4_DISTANCE_CM);

    // Turn Right (zone 6)
    ROBUSMovement_arcMove_turn(COLOR_BLUE, FORWARD, RIGHT_TURN, 90.0);

    ROBUSMovement_arcMove_straight(FORWARD, ZONE4_DISTANCE_CM);

    ROBUSMovement_arcMove_straight(STRAIGHT_RIGHT_TURN, ROBUSMovement_turn_math(88));
    // Straight (zone 6 - 9)
    /*float speedFactor = 0.95f;
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
    ROBUSMovement_stop();*/
    ROBUSMovement_arcMove_straight(FORWARD, 190.0); // 6 pieds
}

void ChallengerSolver_ExecuteRace()
{
    
}