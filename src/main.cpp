#include "ROBUSMovement.hpp"
#include "WhistlesoundDetector.hpp"
#include "WhistleDetector.hpp"
#include "Colour_Sensor/Color_Detector.hpp"
#include "CupWhacker.hpp"
#include "integrationTesting/ROBUSMovement_test.hpp"
#include "Ball_Detector/BallDetector.hpp"
#include "Line_Follower/Line_follower.hpp"

int chosencolor = COLOR_YELLOW;

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

  ROBUSMovement_arcMoveTEST(chosencolor, 90.0, RIGHT_TURN, NOT_USED);
  ROBUSMovement_arcMoveTEST(chosencolor, 0, NOT_USED, STRAIGHT_2_FT);
  ROBUSMovement_arcMoveTEST(chosencolor, 90.0, RIGHT_TURN, NOT_USED);
  ROBUSMovement_arcMoveTEST(chosencolor, 0, NOT_USED, STRAIGHT_8_FT);
  ROBUSMovement_arcMoveTEST(chosencolor, 90.0, RIGHT_TURN, NOT_USED);
  ROBUSMovement_arcMoveTEST(chosencolor, 0, NOT_USED, STRAIGHT_2_FT);
  ROBUSMovement_arcMoveTEST(chosencolor, 90.0, RIGHT_TURN, NOT_USED);
  ROBUSMovement_arcMoveTEST(chosencolor, 0, NOT_USED, STRAIGHT_8_FT);
  ROBUSMovement_EmergencyStop();
  delay(5000);

  /*S3003_SetAngle(1,0);

  delay(3000);

  S3003_SetAngle(1,180);

  delay(3000);*/



  //waitForWhistle();
  /*ColorDetector_detectColor();
  int color=Color_Detection();
  Serial.println(color);*/
}
