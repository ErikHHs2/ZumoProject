#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <Wire.h>
#include <Zumo32U4.h>
#include <Arduino.h>
#include "Kleuren.h"

#define NUM_SENSORS 5

class volgLijn {
public:

  Zumo32U4LineSensors lineSensors;
  Zumo32U4Motors motors;

  void setup();

  void rijdenZwart();
  void rijdenGroen();

  unsigned int lineSensorValues[NUM_SENSORS];

  int maxSpeed = 200;

  int lastError;

  bool useEmitters = true;

};

#endif
