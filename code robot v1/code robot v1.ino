#include <Wire.h>
#include <Zumo32U4.h>
#include <LSM303.h>

Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;

void setup() {
  // put your setup code here, to run once:
// Wait for the button A to be pressed
  buttonA.waitForPress();
  
  // Do something when the button A is pressed
  // For example, turn on the red LED
  ledRed(1);
  
  // Wait for the button A to be released
  buttonA.waitForRelease();
  
  // Do something when the button A is released
  // For example, turn off the red LED
  ledRed(0);
  motors.setSpeeds(100, 100);
}

void loop() {
  // put your main code here, to run repeatedly:
}

