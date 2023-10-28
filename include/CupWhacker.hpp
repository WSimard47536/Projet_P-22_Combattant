/**
 * @file CupWhacker.hpp
 * @author William ()
 * @brief Header file for Cup whacking
 * @version 0.1
 * @date 2023-10-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

//include servo
#include "Distance_sensor/GP2D12.hpp"
#include "Servo_Motors/ServoMotors.hpp"
#include "Color_Detector.hpp"


/**
 * @brief Sets base values
 */
void CupWhacker_Init();

/**
 * @brief Whacks a detected cup
 */
void CupWhacker_WhackCup();