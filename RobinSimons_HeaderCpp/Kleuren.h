#ifndef KLEUREN_H
#define KLEUREN_H


#include <Wire.h>
#include <Zumo32U4.h>
#include <Arduino.h>

#define NUM_SENSORS 5


class Kleuren {
public:

  Zumo32U4LineSensors lineSensors;
  Zumo32U4ButtonA buttonA;
  Zumo32U4Motors motors;

  void calibrateSensors();
  void Groenwaardes();
  int ZwartWardes();
  void bruinWaardes();
  // void printReadingsToSerial();
  void printReadingsToSerial1();

  unsigned int GroenWaarde[NUM_SENSORS];
  unsigned int lineSensorValues[NUM_SENSORS];
  unsigned int ZwartWarde[NUM_SENSORS];

  int GroenMin = 2000;
  int GroenMax = 0;
  int ZwartMin = 2000;
  int ZwartMax = 0;
  int WitMax = 0;
  int WitMin = 2000;
  int bruinMin = 2000;
  int bruinMax = 0;
  bool useEmitters = true;

private:
};

#endif
