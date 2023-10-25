/**
 * @file ServoMotors.hpp
 * @author Lyam BRS (lyam.brs@gmail.com)
 * @brief Header file used for servo motors colour sensor.
 * @version 0.1
 * @date 2023-10-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

/**
 * @brief Initialisation function of a single
 * servo motor based on a given arduino pin
 * number.
 * @param servoMotorPin 
 * Arduino pin number
 */
void S3003_Innit(int servoMotorPin);// servomotor 1 est pour le cup whacker et le 0 est pour le cup placer

/**
 * @brief Simple function that must put the right
 * PWM value at the specified pin.
 * This function should transform a value from 0 to 100
 * into the right PWM number for the servo to reach that
 * position.
 * @param WantedPosition 
 */
void S3003_SetAngle(int servoMotorPin, float WantedPosition);

// I suggest making more functions. You could make one that makes the big number from the smaller number for example.
// The functions you make should start with GROVE_. variables as inputs should be lower camelCase.
