/**
 * @file ServoMotors.hpp
 * @author Lyam BRS (lyam.brs@gmail.com)
 * @brief Header file used for servo motors colour sensor.
 * @version 2 (modified by Mohamed)
 * @date 2023-10-31
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include "LibRobus.h"

#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 180
#define SERVO_CUP_PLACER 0
#define SERVO_CUP_WHACKER 1

/**
 * @brief Initialisation function of a single
 * servo motor based on a given arduino pin
 * number.
 * @param servoMotorPin
 * Arduino pin number
 */
void S3003_Init(unsigned servoMotorPin);

/**
 * @brief Simple function that must put the right
 * PWM value at the specified pin.
 * This function should transform a value from 0 to 100
 * into the right PWM number for the servo to reach that
 * position.
 * @param WantedPosition
 */
void S3003_SetAngle(unsigned servoMotorPin, unsigned WantedPosition);

/**
 * @brief Reset function for the servomotor
 * @param servoMotorPin
 * Arduino pin number
 */
void S3003_setDefault(unsigned servoMotorPin);