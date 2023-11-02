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
  //CupWhacker_Init();
  //CupPlacer_Init();
}

void loop()
{
  // RÉSOLUTION
  startFromBumber();
  //waitForWhistle();
  
  ChallengeSolver_ExecuteFirstLap();
  ChallengeSolver_ExecuteSecondLap();

}
