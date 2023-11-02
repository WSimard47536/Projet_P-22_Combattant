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
  //CupWhacker_Init();
  //CupPlacer_Init();
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

  /*ROBUSMovement_continuousPID_begin_cm(50);
  while(ROBUSMovement_stopRequirementContinuous()){
    ROBUSMovement_momentaryPID_inwhile();
    
    
  }*/

  //ROBUSMovement_arcMove_straight(FORWARD, STRAIGHT_HALF_FT);
  Serial.println(ENCODER_Read(RIGHT_ENCODER));
  //ROBUSMovement_EmergencyStop();
  delay(500);

  

  //waitForWhistle();
  /*ColorDetector_detectColor();
  int color=Color_Detection();
  Serial.println(color);*/
  //CupPlacer_TurnAroundCup();
}
