#include "ROBUSMovement.hpp"
#include "WhistlesoundDetector.hpp"
#include "WhistleDetector.hpp"
#include "Colour_Sensor/Color_Detector.hpp"
#include "CupWhacker.hpp"
#include "integrationTesting/ROBUSMovement_test.hpp"
#include "Ball_Detector/BallDetector.hpp"
#include "Line_Follower/Line_follower.hpp"

int chosencolor = COLOR_GREEN;

void setup() {
  BoardInit();
  //ColorDetector_init();
  CupWhacker_Init();
  /*InitializeProximitySensors();
  ColorDetector_init();*/
  LineFollower_Innit(PA_LINEFOLLOWER);
}

void loop()
{
  
  
  //Serial.println(4800/(analogRead(3)-20));
  //CupWhacker_WhackCup();

  /*Serial.println(CupWhacker_main());
  delay(100);

  if(ROBUS_IsBumper(0)){
    bool isDetected = BallDetector_DetectBall(2);
    Serial.println(isDetected);
  }*/


  
  ROBUSMovement_arcMove_straight(STRAIGHT_RIGHT_TURN, ROBUSMovement_turn_math(86));
  ROBUSMovement_stop();
  delay(500);
  ROBUSMovement_arcMove_straight(STRAIGHT_LEFT_TURN, ROBUSMovement_turn_math(86));
  ROBUSMovement_stop();
  //ROBUSMovement_EmergencyStop();
  delay(500);
  //ROBUSMovement_arcMove_turn(chosencolor, );
  

  /*ROBUSMovement_continuousPID_begin_cm(STRAIGHT_8_FT);
  while(ROBUSMovement_stopRequirementContinuous()){
    ROBUSMovement_momentaryPID_inwhile();


  }*/
  

  

  //MOTOR_SetSpeed(LEFT_MOTOR, 0.5);
  //ROBUSMovement_arcMove_global(chosencolor, 90.0, RIGHT_TURN, NOT_USED);
  //ROBUSMovement_arcMove_global(chosencolor, 0, NOT_USED, STRAIGHT_2_FT);
  //ROBUSMovement_arcMove_global(chosencolor, 90.0, RIGHT_TURN, NOT_USED);
  //ROBUSMovement_arcMove_global(chosencolor, 0, NOT_USED, STRAIGHT_8_FT);
  //ROBUSMovement_arcMove_global(chosencolor, 90.0, RIGHT_TURN, NOT_USED);
  //ROBUSMovement_arcMove_global(chosencolor, 0, NOT_USED, STRAIGHT_2_FT);
  //ROBUSMovement_arcMove_global(chosencolor, 90.0, RIGHT_TURN, NOT_USED);
  //ROBUSMovement_arcMove_global(chosencolor, 0, NOT_USED, STRAIGHT_8_FT);
  //ROBUSMovement_stop();
  

  /*S3003_SetAngle(1,0);

  delay(3000);

  S3003_SetAngle(1,180);

  delay(3000);*/



  //waitForWhistle();
  /*ColorDetector_detectColor();
  int color=Color_Detection();
  Serial.println(color);*/
}
