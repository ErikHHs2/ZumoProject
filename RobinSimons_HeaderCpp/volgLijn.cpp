#include "volgLijn.h"
#include <Wire.h>
#include <Zumo32U4.h>



void volgLijn::setup(){
  lineSensors.initFiveSensors();
}

void volgLijn::rijdenZwart() {
  // Implementatie van rijdenZwart()

  int position = lineSensors.readLine(lineSensorValues);

  int error = position - 2000;

  int speedDifference = 10 * error + 50 * (error - lastError);

  lastError = error;

  Serial.println(position);

  int16_t leftSpeed = (int)maxSpeed + speedDifference;
  int16_t rightSpeed = (int)maxSpeed - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int)maxSpeed);

  static uint16_t lastSampleTime = 0;


  if ((int)(millis() - lastSampleTime) >= 100) {
    lastSampleTime = millis();

    // Read the line sensors.
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);

    // Send the results to the display and to the serial monitor.
    // printReadingsToSerial1();
  }

  motors.setSpeeds(leftSpeed, rightSpeed);
}


void volgLijn::rijdenGroen() {
  // Implementatie van rijdenZwart()

  int position = lineSensors.readLine(lineSensorValues);

  int error = position - 2000;

  int speedDifference = 10 * error + 50 * (error - lastError);

  lastError = error;

  Serial.println(position);

  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  static int lastSampleTime = 0;


  if ((int)(millis() - lastSampleTime) >= 100) {
    lastSampleTime = millis();

    // Read the line sensors.
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);

    // Send the results to the display and to the serial monitor.
    // printReadingsToSerial1();
  }

  motors.setSpeeds((leftSpeed / 2 ), (rightSpeed / 2));
}