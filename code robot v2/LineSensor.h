#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <Zumo32U4.h>

class LineSensor {
public:
  LineSensor();
  void initialize();
  void calibrate();
  uint16_t readSensor(uint8_t sensorNumber);

private:
  Zumo32U4LineSensors lineSensors;
};

#endif
