/**
 * @file ServoMotors.cpp
 * @author Lyam BRS (lyam.brs@gmail.com)
 * @brief File used for servo motor related functions
 * @version 2 (modified by Mohamed)
 * @date 2023-10-31
 * @copyright Copyright (c) 2023
 */

#include "Servo_Motors/ServoMotors.hpp"

/**
 * @brief Initialisation function of a single
 * servo motor based on a given arduino pin
 * number.
 * @param servoMotorPin
 * Arduino pin number
 */
void S3003_Init(unsigned servoMotorPin)
{
    SERVO_Enable(servoMotorPin); // servomotor 1 est pour le cup whacker et le 0 est pour le cup placer
}

/**
 * @brief Simple function that must put the right
 * PWM value at the specified pin.
 * This function should transform a value from 0 to 100
 * into the right PWM number for the servo to reach that
 * position.
 * @param WantedPosition
 */
void S3003_SetAngle(unsigned servoMotorPin, unsigned WantedPosition)
{
    SERVO_SetAngle(servoMotorPin, WantedPosition);
}

void S3003_setDefault(unsigned servoMotorPin)
{
    SERVO_SetAngle(servoMotorPin, SERVO_MAX_ANGLE / 2);
}