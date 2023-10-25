#pragma once
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#define RED 0
#define GREEN 1
#define BLUE 2
#define YELLOW 3
#define BLACK 4
void ColorDetector_init();

void ColorDetector_detectColor();

int Color_Detection();