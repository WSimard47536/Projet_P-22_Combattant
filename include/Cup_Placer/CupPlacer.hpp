/**
 * @file CupPlacer.hpp
 * @author LyamBRS (lyam.brs@gmail.com)
 * @brief Header file of the functions used to place the cup on the ping pong ball
 * @version 0.1
 * @date 2023-10-19
 * @copyright Copyright (c) 2023
 */
#pragma once

/**
 * @brief Function that must initialise everything that is needed
 * to make the cup placer work. This should probably call
 * SERVO init functions.
 */
void CupPlacer_Innit();

/**
 * @brief Function that must place the cup on the detected poing pong ball.
 * This function DOES NOT detect the ball, it only PLACES the cup on the
 * ball. This should probably call SERVO functions.
 */
void CupPlacer_PlaceCup();

// I suggest making more functions. You could make one that makes the big number from the smaller number for example.
// The functions you make should start with CupPlacer_. variables as inputs should be lower camelCase.
