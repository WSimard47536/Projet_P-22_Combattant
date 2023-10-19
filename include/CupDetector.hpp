/**
 * @file CupDetector.hpp
 * @author William ()
 * @brief Header file for Cup detection
 * @version 0.1
 * @date 2023-10-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "Distance_sensor/GP2D12.hpp"

/**
 * @brief Sets base values
 * 
 * @param pinNumber 
 * pin to set (between 0 and 3) (J9-J12)
 */
void CupDetector_Init(int pinNumber);

/**
 * @brief Check if something has been detected
 * 
 * @param pinNumber 
 * pin to set (between 0 and 3) (J9-J12)
 * @return unsigned short
 * 0 if nothing has been detected
 * else if something has been detected
 */
unsigned short CupDetector_GetCup(int pinNumber);

