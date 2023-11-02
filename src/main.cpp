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
  ColorDetector_init();
  ChallengeSolver_Init();
  //CupWhacker_Init();
  //CupPlacer_Init();
}

void loop()
{
  // RÉSOLUTION
  //waitForWhistle();
  waitForBumper();
  ChallengeSolver_ExecuteFirstLap();
  ChallengeSolver_ExecuteSecondLap();

  //ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_6_FT);
  //ROBUSMovement_EmergencyStop();
  //ROBUSMovement_arcMove_straight(STRAIGHT_LEFT_TURN, ROBUSMovement_turn_math(80));
  //ROBUSMovement_EmergencyStop();
  //ROBUSMovement_arcMove_turn(GREEN, FORWARD, RIGHT_TURN, 90.0);
  //ROBUSMovement_stop();

}
