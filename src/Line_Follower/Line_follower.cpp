#include "Line_Follower/Line_follower.hpp"
#include "Arduino.h"

/**
 * @file Line_follower.cpp
 * @author Elodie
 * @brief File containing the functions related to the line follower
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */


/**
 * @brief Function that initialize the line follower sensor (analog pin)
 * 
 * @param LineFollowerPin
 * the pin used for the line follower
 * 
 */

void LineFollower_Innit(int LineFollowerPin){
    pinMode(LineFollowerPin, INPUT);
}

/**
 * @brief Reads the analog pin of the line follower
 * 
 * @param pin
 * the line follower'pin to read from
 * 
 */

int LFP_Read(int LineFollowerPin){
    return analogRead(LineFollowerPin);
}

/**
 * @brief Reads the status of the five sensors of the line follower to chose the movement to do
 * 
 * @return int
 * Value returned depending on the value of the analog read of the sensor
 * -1 : turn far on the left to find the line
 * -2 : turn on the left to find the line
 *  0 : move forward on the line
 *  1 : turn on the right to find the line
 *  2 : turn far on the right to find the line
 * 
 */

int LineFollower_Read(int LineFollowerPin){
    int status = LFP_Read(LineFollowerPin);
    int move = 0;
    
    if (((PA_OOXOO-10) < status) && (status < (PA_OOXOO+10))){ 
        move = FORWARD;
    }

    if ((((PA_OOOOX-10) < status) && (status < (PA_OOOOX+10))) || (((PA_OOOXX-10) < status) && (status < (PA_OOOXX+10)))){
        move = TURN_FAR_RIGHT;
    }

    if ((((PA_OOOXO-10) < status) && (status < (PA_OOOXO+10))) || (((PA_OOXXO-10) < status) && (status < (PA_OOXXO+10)))){ 
        move = TURN_RIGHT;
    }

    if ((((PA_OXXOO-10) < status) && (status < (PA_OXXOO+10))) || (((PA_OXOOO-10) < status) && (status < (PA_OXOOO+10)))){ 
        move = TURN_LEFT;
    }

    if ((((PA_XXOOO-10) < status) && (status < (PA_XXOOO+10))) || (((PA_XOOOO-10) < status) && (status < (PA_XOOOO+10)))){
        move = TURN_FAR_LEFT;
    }

    else{
        move = ERROR;
    }
    return move;
}