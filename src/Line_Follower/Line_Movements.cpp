/**
 * @file Line_Movements.cpp
 * @author LyamBRS (lyam.brs@gmail.com)
 * @brief
 * Contains functions to execute when you want
 * ROBUS to follow a line on the ground.
 * @version 0.1
 * @date 2023-10-30
 * @copyright Copyright (c) 2023
 */

#include "LibRobus.h"
#include "Line_Follower/Line_Movements.hpp"

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define LEFT_ENCODER 0
#define RIGHT_ENCODER 1

/**
 * @brief
 * Simple function that removes the need to call
 * @ref MOTOR_SetSpeed twice when we want to make
 * the robot turn more or less depending on the
 * line that it sees.
 * @param ratio:
 * Ratio from -1 to 1. 0 is forwards
 */
void Movements_SetMotorRatio(float ratio)
{
    float leftRatio = (ratio/2) + 0.5f;
    float rightRatio = -(ratio/2) + 0.5f;

    MOTOR_SetSpeed(LEFT_MOTOR, leftRatio/LINE_MOVEMENT_SPEED_DIVIDER);
    MOTOR_SetSpeed(RIGHT_MOTOR, rightRatio/LINE_MOVEMENT_SPEED_DIVIDER);
}

/**
 * @brief
 * Call this function periodially to make the
 * robot follow the line that is on the ground.
 * Check the returned value to see if the
 * function successfully executed and followed a
 * line when it was called.
 *
 * @attention
 * You may need to call this function multiple
 * time when it no longer detects a line to make
 * sure that there really is no longer a line and
 * that it wasn't just the robot loosing it
 * because of a bump or something.
 *
 * @warning
 * The robot will continue to turn towards where
 * it last saw the line.
 *
 * @return true:
 * A line was found and is currently being
 * followed.
 * @return false:
 * No line is found. by the line following function.
 */
bool Movements_FollowLine()
{
    /**
     * @brief Saves the value of the line in
     * memory so that it can be compared with new
     * values to avoid constantly telling the
     * motors to update to newer values.
     */
    static int previouslySeenLine = 10;
    int lines = LineFollower_Read(PA_LINEFOLLOWER);

    // CHECK // Is the returned value an error value?
    if (lines == ERROR)
    {
        // Stop the robot just to be sure.
        //MOTOR_SetSpeed(LEFT_MOTOR, 0);
        //MOTOR_SetSpeed(RIGHT_MOTOR, 0);
        return false;
    }

    // CHECK // Did the function last set the motors to this value?
    if (previouslySeenLine != lines)
    {
        //previouslySeenLine = lines;
        // CHECK // What is the sensor currently looking at?
        switch(lines)
        {
            case(TURN_FAR_LEFT):
                Movements_SetMotorRatio(LINE_MOVEMENT_RATIO_TURN_FAR_LEFT);
                return true;

            case(TURN_LEFT):
                Movements_SetMotorRatio(LINE_MOVEMENT_RATIO_TURN_LEFT);
                return true;

            case(FORWARD):
                Movements_SetMotorRatio(LINE_MOVEMENT_RATIO_FORWARDS);
                return true;

            case(TURN_RIGHT):
                Movements_SetMotorRatio(LINE_MOVEMENT_RATIO_TURN_RIGHT);
                return true;

            case(TURN_FAR_RIGHT):
                Movements_SetMotorRatio(LINE_MOVEMENT_RATIO_TURN_FAR_RIGHT);
                return true;

            case(ERROR):
                // Should never reach here.
            return false;

            default:
                // There is a serious problem if the program can go here
            return false;
        }
    }
    else
    {
        // The robot did see a line, but the motors were already that value before.
        return true;
    }
    return false;
}