/**
 * @file Line_follower.hpp
 * @author Elodie
 * @brief Header file for the line follower
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#define PA_LINEFOLLOWER  A2 // valeur de la pin analogique pour le suiveur de ligne

#define TURN_FAR_LEFT -2
#define TURN_LEFT -1
#define FORWARD 0
#define TURN_RIGHT 1
#define TURN_FAR_RIGHT 2
#define ERROR 3
#define START 4

/*the X and O are switch - see the green lines in the excel*/

#define PA_OOOOX 980.034
#define PA_OOOXO 947.298
#define PA_OOOXX 914.562
#define PA_OOXOO 875.688
#define PA_OOXXO 812.262
#define PA_OXOOO 748.222
#define PA_OXXOO 613.186
#define PA_XOOOO 491.04
#define PA_XXOOO 229.152
#define PA_XXXXX 0.4092 // ligne de départ


#define MARGE 15

/**
 * @brief Function that initialize the line follower sensor (analog pin)
 * 
 * @param LineFollowerPin
 * the pin used for the line follower
 * 
 */
void LineFollower_Innit(int LineFollowerPin);

/**
 * @brief Reads the analog pin of the line follower
 * 
 * @param pin
 * the line follower'pin to read from
 * 
 */
int LFP_Read(int LineFollowerPin);

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
int LineFollower_Read(int LineFollowerPin);