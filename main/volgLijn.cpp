#include "volgLijn.h"
#include <Wire.h>
#include <Zumo32U4.h>

void volgLijn::setup(){
  // Initialiseer de lijnsensoren
  lineSensors.initFiveSensors();
}

/**
 * @brief Functie voor het volgen van een zwarte lijn.
 */
void volgLijn::rijdenZwart() {
  // Implementatie van rijdenZwart()

  // Lees de positie van de lijnsensoren
  int position = lineSensors.readLine(lineSensorValues);

  // Bereken de fout (error)
  int error = position - 2000;

  // Bereken het snelheidsverschil op basis van de fout
  int speedDifference = 10 * error + 50 * (error - lastError);

  // Bewaar de laatste fout voor gebruik bij de volgende iteratie
  lastError = error;

  Serial.println(position);

  // Bereken de snelheden voor de linker- en rechtermotor
  int16_t leftSpeed = (int)maxSpeed + speedDifference;
  int16_t rightSpeed = (int)maxSpeed - speedDifference;

  // Begrens de snelheden binnen het maximale snelheidsbereik
  leftSpeed = constrain(leftSpeed, 0, (int)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int)maxSpeed);

  static uint16_t lastSampleTime = 0;

  // Voer de lijnsensorlezingen uit met een bepaalde interval
  if ((int)(millis() - lastSampleTime) >= 100) {
    lastSampleTime = millis();

    // Lees de waarden van de lijnsensoren
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);

    // Stuur de resultaten naar het display en de seriële monitor
    // printReadingsToSerial1();
  }

  // Stel de snelheden van de motoren in
  motors.setSpeeds(leftSpeed, rightSpeed);
}

/**
 * @brief Functie voor het volgen van een groene lijn.
 */
void volgLijn::rijdenGroen() {
  // Implementatie van rijdenGroen()

  // Lees de positie van de lijnsensoren
  int position = lineSensors.readLine(lineSensorValues);

  // Bereken de fout (error)
  int error = position - 2000;

  // Bereken het snelheidsverschil op basis van de fout
  int speedDifference = 10 * error + 50 * (error - lastError);

  // Bewaar de laatste fout voor gebruik bij de volgende iteratie
  lastError = error;

  Serial.println(position);

  // Bereken de snelheden voor de linker- en rechtermotor
  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  // Begrens de snelheden binnen het maximale snelheidsbereik
  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  static int lastSampleTime = 0;

  // Voer de lijnsensorlezingen uit met een bepaalde interval
  if ((int)(millis() - lastSampleTime) >= 100) {
    lastSampleTime = millis();

    // Lees de waarden van de lijnsensoren
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);

    // Stuur de resultaten naar het display en de seriële monitor
    // printReadingsToSerial1();
  }

  // Stel de snelheden van de motoren in (gebruik de helft van de snelheid)
  motors.setSpeeds((leftSpeed / 2), (rightSpeed / 2));
}
