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
#include "Servo_Motors.cpp"
#include "GP2D12.cpp"
#include "Color_Detector.cpp"
/**
 * @brief Sets base values
 */
void CupWhacker_Init()
{
    S3003_Innit(1);
}

/**
 * @brief Whacks a detected cup
 */
void CupWhacker_WhackCup()
{
    track_Color = Color_Detection();
    bool b = true; 
    if (track_Color == Yellow){
        while (b){
            if(GP2D12_Read(1)>=0.62f){
                b = false;
            }
        }
        S3003_setAngle(1,180);
        while(!b){
            if(GP2D12_Read(1) < 0.62f){
                b = true;
            }
        }
        S3003_setAngle(1,90);
    }
    else if (track_Color == GREEN){
        while (b){
            if(GP2D12_Read(2)>=0.62f){
                b = false;
            }
        }
        S3003_setAngle(1,0);
        while(!b){
            if(GP2D12_Read(2) < 0.62f){
                b = true;
            }
        }
        S3003_setAngle(1,90);   
 }
}
