/**
 * @file InfraRed.hpp
 * @author Élodie (you@domain.com)
 * @brief Header file used for generic low level functions that reads and utilizes infra red sensors
 * @version 2 (modified by Mohamed)
 * @date 2023-10-31
 * @copyright Copyright (c) 2023
 */

#pragma once
#include <Arduino.h>
#include "LibRobus.h"

#define GREEN_PIN 48
#define RED_PIN 49

/**
 * @brief Initialize an infra red sensor
 * @param pin
 * the pin to initialize
 */
void IR_Init(int pin);

/**
 * @brief Reads the infra red sensor
 * @param pin
 * the infra red's pin to read from
 * @return true
 * returned when something is detected
 * @return false
 * returned when nothing is detected
 */
bool IR_Read(int pin);