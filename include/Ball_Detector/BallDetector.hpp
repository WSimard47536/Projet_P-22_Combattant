/**
 * @file BallDetector.cpp
 * @author Elxhadi (mohamedelhadi.bendjeddou@gmail.com) et Cedetic Sait-louis
 * @brief File of functions used to detect the ball.
 * @version 1.0
 * @date 2023-10-30
 * @copyright Copyright (c) 2023
 */

#pragma once

/**
 * @brief LED's buffer mode initializer using DC2318 proximity sensor.
 */
void BallDetector_Init();

/**
 * @brief Ball detector that uses proximity sensor developed in APP01
 * @param
 * nb_verification: Number of verification used to handle false positives
 * @return Bool
 * True: Ball detected and verified
 * False: No ball
 */
bool BallDetector_DetectBall(unsigned verificationCount);