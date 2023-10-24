#include "ROBUSMovement.hpp"
#include "WhistlesoundDetector.hpp"
#include "WhistleDetector.hpp"
#include "ObstacleDetector.hpp"
#include "Colour_Sensor/Color_Detector.hpp"

#include "integrationTesting/ROBUSMovement_test.hpp"

void setup()
{
  BoardInit();
  InitializeProximitySensors();
  ColorDetector_init();
}

void loop()
{
  //waitForWhistle();
  ColorDetector_detectColor();
  int color=Color_Detection();
  Serial.println(color);
}