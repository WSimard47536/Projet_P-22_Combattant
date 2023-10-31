/**
 * @file DC2318.hpp
 * @author Élodie
 * @brief Header file for the use of the infra red sensor DC2318
 * @version 2 (modified by Mohamed)
 * @date 2023-10-31
 * @copyright Copyright (c) 2023
 */

#pragma once

/**
 * @brief Buzzer function used for acoustic debugging :)
 */
void beep(unsigned count);

/**
 * @brief Fonction that initialize a DC2318 sensor
 * @param leftPin 
 * the pin used for the left IR sensor
 * @param rightPin 
 * the pin used for the right IR sensor
 */
void DC2318_Init(unsigned leftPin, unsigned rightPin);

/**
 * @brief Function for fetching LED's status
 * @return
 * True: If and only if the two LED's are on
 * False: Otherwise
 */
bool DC2318_Read(unsigned leftPin, unsigned rightPin);