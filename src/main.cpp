#include "ROBUSMovement.hpp"
#include "WhistlesoundDetector.hpp"
#include "WhistleDetector.hpp"
#include "ObstacleDetector.hpp"
#include "Colour_Sensor/Color_Detector.hpp"
#include "CupWhacker.hpp"
#include "integrationTesting/ROBUSMovement_test.hpp"
#include "Ball_Detector/BallDetector.hpp"



void setup() {
  BoardInit();
  InitializeProximitySensors();
  //ColorDetector_init();
  CupWhacker_Init();
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

  /*S3003_SetAngle(1,0);

  delay(3000);

  S3003_SetAngle(1,180);

  delay(3000);*/



  //waitForWhistle();
  /*ColorDetector_detectColor();
  int color=Color_Detection();
  Serial.println(color);
  */
  
}

// R2 j12 distance gp2d12 droite 490 a 10cm, 340 a 15 cm , 180 e a 30cm et 120 a 50cm
// R2 j9 distance gp2d12 gauche en 400 a 10cm, 300 a 15 cm , 160 a 30cm et  a 50cm
}

