#include "LineSensor.h"
#include <Wire.h>
#include <Zumo32U4.h>



void LineSensor::setup(){
  lineSensors.initFiveSensors();
}

void LineSensor::rijdenZwart() {
  // Implementatie van rijdenZwart()

  int position = lineSensors.readLine(lineSensorValues);

  uint16_t error = position - 2000;

  uint16_t speedDifference = 10 * error + 50 * (error - lastError);

  lastError = error;

  Serial.println(position);

  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  static uint16_t lastSampleTime = 0;


  if ((uint16_t)(millis() - lastSampleTime) >= 100) {
    lastSampleTime = millis();

    // Read the line sensors.
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);

    // Send the results to the display and to the serial monitor.
    // printReadingsToSerial1();
  }

  motors.setSpeeds(leftSpeed, rightSpeed);
}
