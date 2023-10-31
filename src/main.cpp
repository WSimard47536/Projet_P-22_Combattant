#include "ROBUSMovement.hpp"
#include "WhistlesoundDetector.hpp"
#include "WhistleDetector.hpp"
#include "Colour_Sensor/Color_Detector.hpp"
#include "CupWhacker.hpp"
#include "integrationTesting/ROBUSMovement_test.hpp"
#include "Ball_Detector/BallDetector.hpp"
#include "Line_Follower/Line_follower.hpp"



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

  Serial.println(CupWhacker_main());
  delay(100);

  if(ROBUS_IsBumper(0)){
    bool isDetected = BallDetector_DetectBall(2);
    Serial.println(isDetected);
  }

  /*LineFollower_Read(PA_LINEFOLLOWER);*/
  delay(1200);

  /*S3003_SetAngle(1,0);

  delay(3000);

  S3003_SetAngle(1,180);

  delay(3000);*/



  //waitForWhistle();
  /*ColorDetector_detectColor();
  int color=Color_Detection();
  Serial.println(color);
}
