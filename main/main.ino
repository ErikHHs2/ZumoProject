#include <Wire.h>
#include <Zumo32U4.h>
#include <Arduino.h>

#include "Kleuren.h"
#include "volgLijn.h"

Kleuren kleurtjes;
Zumo32U4LineSensors lineSensors;
VolgLijn zwart;

int GroenMin = 2000;
int GroenMax = 0;
int ZwartMin = 2000;
int ZwartMax = 0;
int WitMin = 2000;
int WitMax = 0;
int bruinMin = 2000;
int bruinMax = 0;
bool useEmitters = true;

unsigned int lineSensorValues[NUM_SENSORS];

/**
 * @brief Setup-functie die eenmaal wordt uitgevoerd wanneer het programma start.
 */
void setup() {
  // Zet de seriële communicatie op
  Serial1.begin(9600);
  
  // Initialiseer de lijnsensoren
  kleurtjes.lineSensors.initFiveSensors();
  
  // Configureer het volgen van de zwarte lijn
  zwart.setup();
  
  // Calibreer de sensoren
  kleurtjes.calibrateSensors();
  
  // Bepaal de waarden voor groen
  kleurtjes.Groenwaardes();
  kleurtjes.Groenwaardes();
  
  // Bepaal de waarden voor bruin
  kleurtjes.bruinWaardes();
}

/**
 * @brief Hoofdprogramma die continue wordt uitgevoerd.
 */
void loop() {
  // Volg de zwarte lijn
  zwart.rijdenZwart();
  
  // Controleer of de lijnsensorwaarden binnen bepaalde grenzen vallen
  if ((GroenMin - 50) < lineSensorValues[0] && lineSensorValues[0] > (GroenMax + 50) ||
      (GroenMin - 50) < lineSensorValues[1] && lineSensorValues[1] > (GroenMax + 50) ||
      (GroenMin - 50) < lineSensorValues[2] && lineSensorValues[2] > (GroenMax + 50) ||
      (GroenMin - 50) < lineSensorValues[3] && lineSensorValues[3] > (GroenMax + 50) ||
      (GroenMin - 50) < lineSensorValues[4] && lineSensorValues[4] > (GroenMax + 50)) {
    // Verhoog de lijnsensorwaarden met 100
    for (int j = 0; j < 5; j++) {
      lineSensorValues[j] = lineSensorValues[j] + 100;
    }
    
    // Ga verder met het volgen van de zwarte lijn
    zwart.rijdenZwart();
  } else if ((bruinMin - 50) < lineSensorValues[0] && lineSensorValues[0] > (bruinMin + 50) ||
             (bruinMin - 50) < lineSensorValues[1] && lineSensorValues[1] > (bruinMin + 50) ||
             (bruinMin - 50) < lineSensorValues[2] && lineSensorValues[2] > (bruinMin + 50) ||
             (bruinMin - 50) < lineSensorValues[3] && lineSensorValues[3] > (bruinMin + 50) ||
             (bruinMin - 50) < lineSensorValues[4] && lineSensorValues[4] > (bruinMin + 50)) {
    // Verhoog de lijnsensorwaarden met 100
    for (int j = 0; j < 5; j++) {
      lineSensorValues[j] = lineSensorValues[j] + 100;
    }
  }
}
