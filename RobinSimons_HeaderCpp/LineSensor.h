#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <Wire.h>
#include <Zumo32U4.h>
#include <Arduino.h>
#include "Kleuren.h"

#define NUM_SENSORS 5

class LineSensor {
public:

  Zumo32U4LineSensors lineSensors;
  Zumo32U4Motors motors;

  void setup();

  void rijdenZwart();

  unsigned int lineSensorValues[NUM_SENSORS];

  uint16_t maxSpeed = 200;

  uint16_t lastError;

  bool useEmitters = true;

};

#endif
