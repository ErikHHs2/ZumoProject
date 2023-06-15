#ifndef PROXIMITYSENSOR_H
#define PROXIMITYSENSOR_H

#include <Wire.h>
#include <Zumo32U4.h>
#include <Arduino.h>
#include "Kleuren.h"

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ProximitySensors proxSensors;

class ProximitySensor : Kleuren{
public:
  void duwBlokje();
  virtual int bruinWaardes();

};

#endif
