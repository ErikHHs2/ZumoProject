#ifndef KLEUR_H
#define KLEUR_H

#include <Zumo32U4.h>



class Kleur 
{
public:
  //Kleur();
  kleur(unsigned int* lineSensorValues);
  void readSensors();
  int getMinimumValue() const;
  int getMaximumValue() const;

private:
  int minValue;
  int maxValue;
  // int sensorValues[5];
  bool useEmitters;
  //Zumo32U4LineSensors lineSensors;
  unsigned int* lineSensorValues[];
};
#endif  // KLEUR_H
