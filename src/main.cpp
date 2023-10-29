#include "ROBUSMovement.hpp"
#include "WhistlesoundDetector.hpp"
#include "WhistleDetector.hpp"
#include "ObstacleDetector.hpp"
#include "Colour_Sensor/Color_Detector.hpp"

#include "integrationTesting/ROBUSMovement_test.hpp"
#include "Line_Follower/Line_follower.hpp"

void setup()
{
  BoardInit();
  /*InitializeProximitySensors();
  ColorDetector_init();*/
  LineFollower_Innit(PA_LINEFOLLOWER);
}

void loop()
{
  //waitForWhistle();
  ColorDetector_detectColor();
  int color=Color_Detection();
  Serial.println(color);
  /*LineFollower_Read(PA_LINEFOLLOWER);*/
  delay(1200);
}