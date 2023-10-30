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
#include "Colour_Sensor/Color_Detector.hpp"

#define INTERVALLE_BRAS 5000
#define DISTANCE_CAPTAGE 30
/**
 * @brief Sets base values
 */
void CupWhacker_Init();

void CupWhacker_Reset();

/**
 * @brief Whacks a detected cup
 */
bool CupWhacker_WhackCup();

bool CupWhacker_main();