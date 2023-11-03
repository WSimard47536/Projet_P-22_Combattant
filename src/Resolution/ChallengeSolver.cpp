#include "Resolution/ChallengeSolver.hpp"

RobotPosition currentRobotPosition;
int assignedColor;

void ChallengeSolver_Init()
{
    currentRobotPosition.positionX_pulses = 0; //START POSITION_x
    //assignedColor = Color_Detection();
    assignedColor = GREEN;
}

/*float GetRobotOrientation()
{
    // Faire arctan pour avoir en degrés
    //return (position.positionX_pulses % FULL_ROTATIONS_PULSES) / (position.positionY_pulses % FULL_ROTATIONS_PULSES);
}*/

void waitForBumper(int bumberNumber){
    bool status = true;
    while(status){
        int state = ROBUS_IsBumper(bumberNumber); 
        if (state == 1)
        {
            status = false;
        }
        delay(100);
    }
}

void startFromBumber(){
    bool status = true;
    int state_R = 0;
    int state_L = 0;
    int state_B = 0;
    while(status){
        int state_R = ROBUS_IsBumper(BUMBER_RIGHT); 
        int state_L = ROBUS_IsBumper(BUMBER_RIGHT);
        int state_B = ROBUS_IsBumper(BUMBER_BACK);
        if (state_R == 1)
        {
            status = false;
            assignedColor = GREEN;
        }
        else if (state_L == 1)
        {
            status = false;
            assignedColor = YELLOW;
        }
        else if (state_B == 1)
        {
            status = false;
            assignedColor = Color_Detection();
        }
        delay(50);
    }
}

void ChallengeSolver_ExecuteAllSteps()
{

}

void ChallengeSolver_dropCupTime(){
    CupPlacer_PlaceCup();
    delay(500);
    CupPlacer_TurnAroundCup();
    ROBUSMovement_arcMove_straight(FORWARD, 259.08); // 8 pieds et demi
}

void ChallengeSolver_TotallyFollowingTheLine(){
    assignedColor = YELLOW;
    ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_HALF_FT);
    if (assignedColor == YELLOW)
    {
        ROBUSMovement_arcMove_straight(2, ROBUSMovement_turn_math(85));
        ROBUSMovement_arcMove_straight(FORWARD, (2*STRAIGHT_HALF_FT));
        ROBUSMovement_arcMove_straight(3, ROBUSMovement_turn_math(DEGREE_45));
    }
    else
    {
        ROBUSMovement_arcMove_straight(STRAIGHT_RIGHT_TURN, ROBUSMovement_turn_math(DEGREE_45));
    }
    ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_DIAG_LINE_1);
    ROBUSMovement_arcMove_straight(2, ROBUSMovement_turn_math(DEGREE_45));
    ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_LINE);
    ROBUSMovement_arcMove_straight(2, ROBUSMovement_turn_math(DEGREE_45));
    ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_DIAG_LINE_2);
    ROBUSMovement_arcMove_straight(2, ROBUSMovement_turn_math(DEGREE_45));
}

void ChallengeSolver_ExecuteRaceLap(int color)
{
    // Turn Right (zone 1)
    ROBUSMovement_arcMove_turn(color, FORWARD, RIGHT_TURN, 90.0);

    // Straight (zone 2)
    if (color == GREEN){
        ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_2_FT*0.8);
    } 
    else if (color==YELLOW){
        ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_2_FT*1.5);
    }

    // Turn Right (zone 3)
    ROBUSMovement_arcMove_turn(color, FORWARD, RIGHT_TURN, 90.0);

    // Move Straight and Whack the cup (zone 4 - 5)
    ROBUSMovement_continuousPID_begin_cm(STRAIGHT_8_FT);
    while (ROBUSMovement_stopRequirementContinuous())
    {
        ROBUSMovement_momentaryPID_inwhile();
    }
    //ROBUSMovement_EmergencyStop();

    //ChallengeSolver_TotallyFollowingTheLine();
    ROBUSMovement_arcMove_turn(color, FORWARD, RIGHT_TURN, 90.0);\

    if (assignedColor == GREEN){
        ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_2_FT*0.8);
    } 
    else if (assignedColor==YELLOW){
        ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_2_FT*1.3);
    }
    
    ROBUSMovement_arcMove_turn(color, FORWARD, RIGHT_TURN, 90.0);
    
    ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_8_FT);    
}

void ChallengeSolver_ExecuteFirstLap()
{
    // Turn Right (zone 1)
    ROBUSMovement_arcMove_turn(assignedColor, FORWARD, RIGHT_TURN, 90.0);

    // Straight (zone 2)
    if (assignedColor == GREEN){
        ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_2_FT*0.8);
    } 
    else if (assignedColor==YELLOW){
        ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_2_FT*1.5);
    }

    // Turn Right (zone 3)
    ROBUSMovement_arcMove_turn(assignedColor, FORWARD, RIGHT_TURN, 90.0);

    // Move Straight and Whack the cup (zone 4 - 5)
    ROBUSMovement_continuousPID_begin_cm(STRAIGHT_8_FT);
    while (ROBUSMovement_stopRequirementContinuous())
    {
        ROBUSMovement_momentaryPID_inwhile();
        //CupWhacker_main(assignedColor);
    }
    //ROBUSMovement_EmergencyStop();

    //ChallengeSolver_TotallyFollowingTheLine();
    ROBUSMovement_arcMove_turn(assignedColor, FORWARD, RIGHT_TURN, 90.0);\

    if (assignedColor == GREEN){
        ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_2_FT*0.8);
    } 
    else if (assignedColor==YELLOW){
        ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_2_FT*1.3);
    }
    
    ROBUSMovement_arcMove_turn(assignedColor, FORWARD, RIGHT_TURN, 90.0);
    
    ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_8_FT);
    


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
    //ChallengeSolver_dropCupTime();

    
}

void ChallengeSolver_ExecuteSecondLap()
{
    // Turn Right (zone 1)
    ROBUSMovement_arcMove_turn(COLOR_GREEN, FORWARD, RIGHT_TURN, 90.0);

    // Straight (zone 2)
    ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_2_FT);

    // Turn Right (zone 3)
    ROBUSMovement_arcMove_turn(COLOR_GREEN, FORWARD, RIGHT_TURN, 95.0);

    // Straight (zone 4 - 5)
    ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_6_FT);

    ROBUSMovement_EmergencyStop();

    // Turn Right (zone 6)
    //ROBUSMovement_arcMove_turn(COLOR_BLUE, FORWARD, RIGHT_TURN, 90.0);
    if (assignedColor == YELLOW) ROBUSMovement_arcMove_straight(STRAIGHT_LEFT_TURN, ROBUSMovement_turn_math(72));
    else if (assignedColor == GREEN) ROBUSMovement_arcMove_straight(STRAIGHT_LEFT_TURN, ROBUSMovement_turn_math(85));

    

    ROBUSMovement_arcMove_straight(FORWARD, ZONE4_DISTANCE_CM); // 4 pieds devraient être en masse

    ROBUSMovement_EmergencyStop();

    ROBUSMovement_arcMove_straight(STRAIGHT_LEFT_TURN, ROBUSMovement_turn_math(70));
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
    ROBUSMovement_arcMove_straight(FORWARD, 200); 
    ROBUSMovement_EmergencyStop();
}


void ChallengerSolver_ExecuteRace()
{
    
}