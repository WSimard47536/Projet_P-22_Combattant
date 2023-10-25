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

#include "CupDetector.hpp"
#include <Arduino.h>
#include "ROBUSMovement.hpp"
/**
 * @brief Sets base values
 */
void CupDetector_Init()
{

}


/**
 * @brief Check if something has been detected
 * 
 * @return unsigned short
 * 0 if nothing has been detected
 * else if something has been detected
 */


int sensor (int pin);
void drop_the_cup(int distance_bt_ball);

unsigned short CupDetector_GetCup()
{

  //  uint16_t ROBUS_ReadIR(uint8_t id);

    // pin 54 to 57
    const int PIN_UP = A3;
    const int PIN_DOWN = A2;
    int distance_up = sensor (PIN_UP);
    int distance_down = csencr (PIN_DOWN);
    // la distance des capteurs est la même 
    if ( distance_up - 4 < distance_down && distance_up + 4 > distance_down){
        return distance_down;
    }
    // detecte la balle 
    if (distance_down < 25){
        drop_the_cup (distance_down);
        retrun distance_down ;
    }
    return 0;
}
int sensor (int pin){
    //https://github.com/qub1750ul/Arduino_SharpIR/blob/master/examples/getDistance/getDistance.ino
    int distance = 4800/(analogRead(pin)-20);
		if(distance > 80) return 81;
		else if(distance < 10) return 9;
		else return distance;
}


/*----------------------------------------------------------------------*/

void drop_the_cup(int distance_bt_ball){
   ROBUSMovement_moveStraight(FORWARD, 0.2, distance_bt_ball + 2);

   SERVO_SetAngle(1,180);
   ROBUSMovement_moveStraight(BACKWARD, 0.2, distance_bt_ball + 2);
}

