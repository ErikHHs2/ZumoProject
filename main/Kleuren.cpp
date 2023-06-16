#include "Kleuren.h"

void Kleuren::calibrateSensors() {
  // Kalibreer de sensoren

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

/**
 * @brief Lees en kalibreer de groene waardes van de lijnsensoren
 * @return Een array met de groene waardes van de lijnsensoren
 */
int Kleuren::Groenwaardes() {
  // Lees en kalibreer de groene waardes van de lijnsensoren
  static int lastSampleTime = 0;

  buttonA.waitForButton();

  if ((int)(millis() - lastSampleTime) >= 100) {
    lastSampleTime = millis();

    // Lees de lijnsensoren uit
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

/**
 * @brief Lees en kalibreer de zwarte waardes van de lijnsensoren
 * @return Een array met de zwarte waardes van de lijnsensoren
 */
int Kleuren::ZwartWardes() {
  // Lees en kalibreer de zwarte waardes van de lijnsensoren
  static int lastSampleTime = 0;

  buttonA.waitForButton();

  if ((int)(millis() - lastSampleTime) >= 100) {
    lastSampleTime = millis();

    // Lees de lijnsensoren uit
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

/**
 * @brief Lees en kalibreer de bruine waardes van de lijnsensoren
 * @return Een array met de bruine waardes van de lijnsensoren
 */
int Kleuren::bruinWaardes() {
  // Lees en kalibreer de bruine waardes van de lijnsensoren

  static int lastSampleTime = 0;

  buttonA.waitForButton();

  if ((int)(millis() - lastSampleTime) >= 100) {
    lastSampleTime = millis();

    // Lees de lijnsensoren uit
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
  // Print de waarden van de lijnsensoren naar de seriële monitor
  lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);

  char buffer[80];
  sprintf(buffer, "%4d %4d %4d %4d %4d %c\n",
          lineSensorValues[0],
          lineSensorValues[1],
          lineSensorValues[2],
          lineSensorValues[3],
          lineSensorValues[4],
          useEmitters ? 'E' : 'e');
  Serial.print(buffer);
}
