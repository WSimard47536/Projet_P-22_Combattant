/**
 * @attention This file is never used due to last minute design change !
 */

#include "Ball_Detector/BallDetector.hpp"
#include "Cup_Placer/CupPlacer.hpp"
#include "Proximity_sensors/DC2318.hpp"
#include "Proximity_sensors/InfraRed.hpp"

// void BallDetector_Init()
// {
// 	DC2318_Init(GREEN_PIN, RED_PIN);
// }
// /**
//  * @attention This function should be called as near as possible to the ball.
//  * Also, the mouvement functions should garantee a staight mouvement on the black line, and they must slow down near it.
//  *
// */
// bool

// BallDetector_DetectBall(unsigned verificationCount)
// {
// 	BallDetector_Init();
// 	// La balle est presente
// 	if (DC2318_Read(GREEN_PIN, RED_PIN))
// 	{
// 		// Arrete et faire verificationCount de verifications
// 		// TODO: add this
// 		// RobusMouvement_stop();
// 		unsigned detectionCount = 0;
// 		for (size_t i = 0; i < verificationCount; ++i)
// 		{
// 			if (DC2318_Read(GREEN_PIN, RED_PIN))
// 				++detectionCount;
// 		}
// 		if (detectionCount == verificationCount)
// 		{
// 			// Bien verifie, drop le cup now
// 			CupPlacer_PlaceCup();
// 			// TODO: maybe remove this delay and the later reset fucntion
// 			delay(1000);
// 			CupPlacer_Reset();
// 			// TODO: ADD your fonctions here for mouvement
// 			return true;
// 		}

// 		else
// 			return false;
// 	}
// 	else
// 		return false;
// }