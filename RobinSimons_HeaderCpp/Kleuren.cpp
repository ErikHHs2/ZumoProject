#include "Kleuren.h"


void Kleuren::calibrateSensors() {
  // Implementatie van calibrateSensors()

  buttonA.waitForButton();

  delay(1000);
  for (int i = 0; i < 120; i++) {
    delay(10);
    if (i > 30 && i <= 90) {
      motors.setSpeeds(-200, 200);
    } else {
      motors.setSpeeds(200, -200);
    }

    lineSensors.calibrate();
  }
  motors.setSpeeds(0, 0);
}

int Kleuren::Groenwaardes() {
  // Implementatie van Groenwaardes()
  static int lastSampleTime = 0;

  buttonA.waitForButton();

  if ((int)(millis() - lastSampleTime) >= 100) {
    lastSampleTime = millis();

    // Read the line sensors.
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);
    for (int i = 0; i < 5; i++) {
      GroenWaarde[i] = lineSensorValues[i];
      if (GroenMax < GroenWaarde[i]) {
        GroenMax = GroenWaarde[i];
      } else if (GroenMin > GroenWaarde[i]) {
        GroenMin = GroenWaarde[i];
      }
    }
  }
  return GroenWaarde;
}

int Kleuren::ZwartWardes() {
  // Implementatie van ZwartWardes()
  static int lastSampleTime = 0;

  buttonA.waitForButton();

  if ((int)(millis() - lastSampleTime) >= 100) {
    lastSampleTime = millis();

    // Read the line sensors.
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);
    for (int i = 0; i < 5; i++) {
      ZwartWarde[i] = lineSensorValues[i];
      if (ZwartMax < ZwartWarde[i]) {
        ZwartMax = ZwartWarde[i];
      } else if (ZwartMin > ZwartWarde[i]) {
        ZwartMin = ZwartWarde[i];
      }
    }
  }
  return ZwartWarde;
}

int Kleuren::bruinWaardes() {

    static int lastSampleTime = 0;

    buttonA.waitForButton();

  if ((int)(millis() - lastSampleTime) >= 100) {
    lastSampleTime = millis();

    // Read the line sensors.
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);
    for (int i = 0; i < 5; i++) {
      BruinWaarde[i] = lineSensorValues[i];
      if (bruinMax < BruinWaarde[i]) {
        bruinMax = BruinWaarde[i];
      } else if (bruinMin > BruinWaarde[i]) {
        bruinMin = BruinWaarde[i];
      }
    }
  }
  return BruinWaarde;
}



void Kleuren::printReadingsToSerial() {
  // Implementatie van printReadingsToSerial1()
  lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);

  char buffer[80];
  sprintf(buffer, "%4d %4d %4d %4d %4d %c\n",
          ZwartWarde[0],
          ZwartWarde[1],
          ZwartWarde[2],
          ZwartWarde[3],
          ZwartWarde[4],
          useEmitters ? 'E' : 'e');
  Serial.print(buffer);
}
