#include "Colour_Sensor/Color_Detector.hpp"

// our RGB -> eye-recognized gamma color
byte gammatable[256];


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void ColorDetector_init() {
    Serial.begin(9600);
    Serial.println("Color View Test!");

    if (tcs.begin()) {
        Serial.println("Found sensor");
    } else {
        Serial.println("No TCS34725 found ... check your connections");
        while (1); // halt!
    }
}


void ColorDetector_detectColor() {
    uint16_t clear, red, green, blue;

    tcs.setInterrupt(false);      // turn on LED

    delay(60);  // takes 50ms to read

    tcs.getRawData(&red, &green, &blue, &clear);

    tcs.setInterrupt(true);  // turn off LED

    Serial.print("C:\t"); Serial.print(clear);
    Serial.print("\tR:\t"); Serial.print(red);
    Serial.print("\tG:\t"); Serial.print(green);
    Serial.print("\tB:\t"); Serial.println(blue);
}

int Detect_Red()
{
    uint16_t clear, red, green, blue;

    tcs.setInterrupt(false);      // turn on LED

    delay(60);  // takes 50ms to read

    tcs.getRawData(&red, &green, &blue, &clear);

    tcs.setInterrupt(true);  // turn off LED

    return red;
}

int Detect_Green()
{
    uint16_t clear, red, green, blue;

    tcs.setInterrupt(false);      // turn on LED

    delay(60);  // takes 50ms to read

    tcs.getRawData(&red, &green, &blue, &clear);

    tcs.setInterrupt(true);  // turn off LED

    return green;
}

int Detect_Blue()
{
    uint16_t clear, red, green, blue;

    tcs.setInterrupt(false);      // turn on LED

    delay(60);  // takes 50ms to read

    tcs.getRawData(&red, &green, &blue, &clear);

    tcs.setInterrupt(true);  // turn off LED

    return blue;
}

int Detect_Clear()
{
    uint16_t clear, red, green, blue;

    tcs.setInterrupt(false);      // turn on LED

    delay(60);  // takes 50ms to read

    tcs.getRawData(&red, &green, &blue, &clear);

    tcs.setInterrupt(true);  // turn off LED

    return clear;  
}

int Color_Detection() 
{
    int red, green, blue, clear;
    int color;
    red = Detect_Red();
    green = Detect_Green();
    blue = Detect_Blue();
    clear = Detect_Clear();

    if (red>green && red>blue)
    {
        if (clear>150)
        {
            color = YELLOW;
        }
        else
        {
            color = RED;
        }
    }

    if (blue>green && blue>red)
    {
        if (clear< 120)
        {
           color = RED;
        }
        
        else
        {
            color = BLUE;
        }
        
    }

    if (green>blue && green>red)
    {
        if (clear>102)
        {
            color = GREEN;
        }
        
        else
        {
           color = GREEN; 
        }
        
    }

    return color;
    
}