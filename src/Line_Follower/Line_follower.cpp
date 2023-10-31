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
 *  3 : error
 *  4 : ligne de départ
 * 
 */

int LineFollower_Read(int LineFollowerPin){
    int status = LFP_Read(LineFollowerPin);
    Serial.println(status);
    int move = 0;
    
    if (((PA_OOXOO-MARGE) < status) && (status < (PA_OOXOO+MARGE))){ 
        move = FORWARD;
    }

    else if (((PA_OOOOX-MARGE) < status) && (status < (PA_OOOOX+MARGE))){
        move = TURN_FAR_RIGHT;
    }

    else if (((PA_OOOXX-MARGE) < status) && (status < (PA_OOOXX+MARGE))){
        move = TURN_FAR2_RIGHT;
    }

    else if (((PA_OOOXO-MARGE) < status) && (status < (PA_OOOXO+MARGE))) { 
        move = TURN_RIGHT;
    }

    else if (((PA_OOXXO-MARGE) < status) && (status < (PA_OOXXO+MARGE))){
        move = TURN_LITTLE_RIGHT;
    }

    else if (((PA_OXXOO-MARGE) < status) && (status < (PA_OXXOO+MARGE))){ 
        move = TURN_LITTLE_LEFT;
    }

    else if (((PA_OXOOO-MARGE) < status) && (status < (PA_OXOOO+MARGE))){
        move = TURN_LEFT;
    }

    else if (((PA_XXOOO-MARGE) < status) && (status < (PA_XXOOO+MARGE))){
        move = TURN_FAR2_LEFT;
    }

    else if (((PA_XOOOO-MARGE) < status) && (status < (PA_XOOOO+MARGE))){
        move = TURN_FAR_LEFT;
    }

    else if ((0 < status) && (status < PA_XXXXX)){
        move = START;
    }
        
    else{
        move = ERROR;
    }
    Serial.println(move);
    return move;
}