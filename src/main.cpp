#include <Arduino.h>
#include "LibRobus.h"
#include "../include/Ball_Detector/BallDetector.hpp"



void setup() {
  BoardInit();
}

void loop() {
  if(ROBUS_IsBumper(0)){
    bool isDetected = BallDetector_DetectBall(2);
    Serial.println(isDetected);
  }

}

