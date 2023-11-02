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

int chosencolor = COLOR_GREEN;

void setup() {
  BoardInit();
  //ColorDetector_init();
  CupWhacker_Init();
  /*InitializeProximitySensors();
  ColorDetector_init();*/
  LineFollower_Innit(PA_LINEFOLLOWER);
  CupPlacer_Init();
  ChallengeSolver_Init();
}

void loop()
{
  // RÉSOLUTION
  /*waitForWhistle();

  ChallengeSolver_ExecuteFirstLap();
  ChallengeSolver_ExecuteSecondLap();*/
  // RÉSOLUTION

  delay(3000);
  CupPlacer_PlaceCup();
  delay(500);

  CupPlacer_TurnAroundCup();
}
