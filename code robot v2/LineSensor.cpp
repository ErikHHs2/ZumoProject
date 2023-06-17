#include "LineSensor.h"

LineSensor::LineSensor() {
  
}

void LineSensor::initialize() {
  lineSensors.initFiveSensors();
}

void LineSensor::calibrate() {
  lineSensors.calibrate();
}

uint16_t LineSensor::readSensor(uint8_t sensorNumber) {
  return lineSensors.readLine(sensorNumber);
}
