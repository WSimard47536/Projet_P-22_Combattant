
#include "Ball_Detector/BallDetector.hpp"
#include "Cup_Placer/CupPlacer.hpp"
#include "Proximity_sensors/DC2318.hpp"
#include "Proximity_sensors/InfraRed.hpp"

void BallDetector_Init()
{
	DC2318_Init(GREEN_PIN, RED_PIN);
}

bool BallDetector_DetectBall(unsigned verificationCount)
{
	BallDetector_Init();
	// La balle est presente
	if (DC2318_Read(GREEN_PIN, RED_PIN))
	{
		// Arrete et faire verificationCount de verifications
		// TODO: add this 
		// RobusMouvement_stop();
		unsigned detectionCount = 0;
		for (size_t i = 0; i < verificationCount; ++i)
		{
			if (DC2318_Read(GREEN_PIN, RED_PIN))
				++detectionCount;
		}
		if (detectionCount == verificationCount)
		{
			// Bien verifie, drop le cup now
			CupPlacer_PlaceCup();
			// TODO: maybe remove this delay and the later reset fucntion
			delay(500);
			CupPlacer_Reset();
			// TODO: implement these in a seperate unit with their interfaces
			// Fonctions pour esquiver le cup
			// RobusMouvement(LEFT, x)
			// RobusMouvement(STRAIGHT, x)
			return true;
		}

		else
			return false;
	}
	else
		return false;
}