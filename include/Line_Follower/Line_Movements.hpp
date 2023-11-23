/**
 * @file Line_Movements.hpp
 * @author LyamBRS (lyam.brs@gmail.com)
 * @brief
 * Contains functions to execute when you want
 * ROBUS to follow a line on the ground.
 * @version 0.1
 * @date 2023-10-30
 * @copyright Copyright (c) 2023
 */

#pragma once

#include "Line_Follower/Line_follower.hpp"

/// @brief The ratio between the right and the left wheel when turning full left
#define LINE_MOVEMENT_RATIO_TURN_FARTHER_LEFT -1.0f
/// @brief The ratio between the right and the left wheel when turning full left
#define LINE_MOVEMENT_RATIO_TURN_FAR_LEFT -0.65f
/// @brief The ratio between the right and the left wheel when turning left
#define LINE_MOVEMENT_RATIO_TURN_LEFT -0.5f
/// @brief The ratio between the right and the left wheel when turning left
#define LINE_MOVEMENT_RATIO_TURN_LITTLE_LEFT -0.25f
/// @brief The ratio between the right and the left wheel when going forwards
#define LINE_MOVEMENT_RATIO_FORWARDS 0
/// @brief The ratio between the right and the left wheel when turning right
#define LINE_MOVEMENT_RATIO_TURN_LITTLE_RIGHT 0.25f
/// @brief The ratio between the right and the left wheel when turning right
#define LINE_MOVEMENT_RATIO_TURN_RIGHT 0.5f
/// @brief The ratio between the right and the left wheel when turning full right
#define LINE_MOVEMENT_RATIO_TURN_FAR_RIGHT 0.65f
/// @brief The ratio between the right and the left wheel when turning full right
#define LINE_MOVEMENT_RATIO_TURN_FARTHER_RIGHT 1.0f
/// @brief How much should movements be divided by. If 1, forwards will be 0.5, max turn will be 0,1
#define LINE_MOVEMENT_SPEED_DIVIDER 5



/**
 * @brief
 * Simple function that removes the need to call
 * @ref MOTOR_SetSpeed twice when we want to make
 * the robot turn more or less depending on the
 * line that it sees.
 * @param ratio:
 * Ratio from -1 to 1. 0 is forwards
 */
void Movements_SetMotorRatio(float ratio);

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
 * @return false
 */
bool Movements_FollowLine();