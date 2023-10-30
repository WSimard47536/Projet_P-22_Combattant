/**
 * @file CupWhacker.cpp
 * @author William, Trévys()
 * @brief Source file for Cup whacking
 * @version 0.1
 * @date 2023-10-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
// TODO:  Might be useless.
#include "CupWhacker.hpp"
int track_Color;

bool status = 0;

/**
 * @brief Sets base values
 */
void CupWhacker_Init()
{
    S3003_Innit(1);
    S3003_SetAngle(1,90);
}

void CupWhacker_Reset()
{
    S3003_SetAngle(1,90);
    status = 0;
}



/**
 * @brief Whacks a detected cup
 */
bool CupWhacker_WhackCup()
{
    Serial.println("IN WHACKCUP");
    track_Color = YELLOW;
    //track_Color = Color_Detection();
    if (track_Color == YELLOW){
        if(GP2D12_Read(3) < DISTANCE_CAPTAGE){
            S3003_SetAngle(1,0);
            Serial.println("changed angle");
            return 1;
        }
    }
    else if (track_Color == GREEN){
        if(GP2D12_Read(0) < DISTANCE_CAPTAGE){
            S3003_SetAngle(1,180);
            return 1;
        }   
    }
    return 0;
 
}

bool CupWhacker_main(){
    int startTime = 0;
    switch (status){
        case 0: 
        status = CupWhacker_WhackCup();
        if (status == 1) startTime = millis();
        break;
        case 1: 
        if ((millis() - startTime) >= INTERVALLE_BRAS){
            S3003_SetAngle(1,90);
            return 1;
        }
        break;
    }
    return 0;
}