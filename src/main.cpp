#include "ROBUSMovement.hpp"
#include "WhistlesoundDetector.hpp"
#include "WhistleDetector.hpp"
#include "Colour_Sensor/Color_Detector.hpp"
#include "CupWhacker.hpp"
#include "integrationTesting/ROBUSMovement_test.hpp"
#include "Ball_Detector/BallDetector.hpp"
#include "Line_Follower/Line_follower.hpp"
#include "Cup_Placer/CupPlacer.hpp"
#include "Resolution/ChallengeSolver.hpp"

void setup() {
  BoardInit();
  ColorDetector_init();
  ChallengeSolver_Init();
}

void loop()
{
  startFromBumber();
  // SI PREMIER JAUNE FAIRE LES AUTRES VERT SINON VERT
  ROBUSMovement_arcMove_straight(FORWARD, 13.0);
  ChallengeSolver_ExecuteRaceLap(YELLOW);
  
  ChallengeSolver_ExecuteRaceLap(GREEN);
  ChallengeSolver_ExecuteRaceLap(GREEN);
  ChallengeSolver_ExecuteRaceLap(GREEN);
  ChallengeSolver_ExecuteRaceLap(GREEN);
  ChallengeSolver_ExecuteRaceLap(GREEN);
  ChallengeSolver_ExecuteRaceLap(GREEN);
  ChallengeSolver_ExecuteRaceLap(GREEN);
  ChallengeSolver_ExecuteRaceLap(GREEN);
  ChallengeSolver_ExecuteRaceLap(GREEN);
  ChallengeSolver_ExecuteRaceLap(GREEN);
  ChallengeSolver_ExecuteRaceLap(GREEN);
  ChallengeSolver_ExecuteRaceLap(GREEN);
  ChallengeSolver_ExecuteRaceLap(GREEN);
  ChallengeSolver_ExecuteRaceLap(GREEN);
}
