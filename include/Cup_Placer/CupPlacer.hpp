/**
 * @file CupPlacer.cpp
 * @author Elxhadi (mohamedelhadi.bendjeddou@gmail.com) et Cedetic Sait-louis
 * @brief File of functions used to drop the cup.
 * @version 1.0
 * @date 2023-10-30
 * @copyright Copyright (c) 2023
 */
#pragma once
#include "../include/Servo_Motors/ServoMotors.hpp"

/**
 * @brief Initializer of the servomotor mode and initial angle
*/
void CupPlacer_Init();

/**
 * @brief Placing cup function that uses servomotor as a pulling force 
*/
void CupPlacer_PlaceCup();


/**
 * @brief Reinitialiser of the servomotor mode and initial angle
*/
void CupPlacer_Reset();

/**
 * @brief Turn around the cup when it is on the ground
 * 
 */
void CupPlacer_TurnAroundCup();