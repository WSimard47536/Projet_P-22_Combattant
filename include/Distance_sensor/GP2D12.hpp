/**
 * @file GP2D12.hpp
 * @author William ()
 * @brief Header file for GP2D12 distance sensor
 * @version 0.1
 * @date 2023-10-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include <LibRobus.h>
/**
 * @brief Sets base values
 * 
 * @param pinNumber 
 * pin to set (between 0 and 3) (J9-J12)
 */
void GP2D12_Innit(int pinNumber);

/**
 * @brief Reads the IR sensor at specified pin
 * 
 * @param pinNumber 
 * pin to read (between 0 and 3)
 * @return unsigned short
 * raw data (16 bits)
 */
float GP2D12_Read(int pinNumber);