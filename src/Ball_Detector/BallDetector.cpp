/**
 * @file BallDetector.cpp
 * @author LyamBRS (lyam.brs@gmail.com)
 * @brief File of functions used to detect the ball.
 * @version 0.1
 * @date 2023-10-19
 * 
 * @copyright Copyright (c) 2023
 * 
 * @warning USE THE DEFINE HEADER FILE TO PUT YOUR DEFINES.
 */
#include "Ball_Detector/BallDetector.hpp"

/**
 * @brief Function that should initialise everything
 * needed for the ball detector to work. Do not manually
 * initialise using pinMode in this function. You must
 * call initializers of other functions.
 */
void BallDetector_Innit()
{

}

/**
 * @brief This function should return if a ball is
 * detected or not when called. Use DistanceSensor
 * functions for this. Do not put all the code in
 * this function.
 * @return unsigned char 
 * 0: No ball
 * 1: Ball on the left
 * 2: Ball on the right
 * 3: Ball on both sides (error)
 */
unsigned char BallDetector_DetectBall()
{

}

// I suggest making more functions. You could make one that makes the big number from the smaller number for example.
// The functions you make should start with BallDetector_. variables as inputs should be lower camelCase.
