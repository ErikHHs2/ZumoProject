#include "Kleur.h"
#include <Zumo32U4.h>


Kleur::Kleur() {
  minValue = 0;
  maxValue = 0;
  useEmitters = true;
  }

Kleur::Kleur(unsigned int* lineSensorValues) {
  // this->lineSensorValues = sensorValues;
  minValue = lineSensorValues[0];
  maxValue = lineSensorValues[0];
  useEmitters = true;
}

// Read line sensor values using Zumo32U4 library
void Kleur::readSensors() {
  //int sensorValues[5];
  for (int i = 0; i < 5; i++) {
       
    ///sensorValues[i] = lineSensorValues(i);

    if (lineSensorValues[i] < minValue) {
      minValue = lineSensorValues[i];
    }
    if (lineSensorValues[i] > maxValue) {
      maxValue = lineSensorValues[i];
    }
  }
}

int Kleur::getMinimumValue() const {
  return minValue;
}

int Kleur::getMaximumValue() const {
  return maxValue;
}
