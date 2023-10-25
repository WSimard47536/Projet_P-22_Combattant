/**
 * @file CupDetector.cpp
 * @author William ()
 * @brief Source file for Cup detection
 * @version 0.1
 * @date 2023-10-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "GP2D12.hpp"
#include "CupDetector.hpp"
#include "Distance_Sensor.cpp"
#include "Colour_Sensor.cpp"
/**
 * @brief Sets base values
 */
void CupDetector_Innit()
{

}

/**
 * @brief Check if something has been detected
 * 
 * @return unsigned short
 * 0 if nothing has been detected
 * else if something has been detected
 */
unsigned short CupDetector_GetCup()
{
    return 0;
}
//TODO: set angle for servomotor depending on the color of the track(y = 180 et g = 0) and distance(50cm)