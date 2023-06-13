#include <Wire.h>
#include <Zumo32U4.h>
#include "kleur.h"

Zumo32U4LineSensors lineSensors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];
unsigned int copiedSensorValues[NUM_SENSORS];


// Calibreer de kleuren in de volgende volgorde:
// zwart
// bruin
// groen
// grijs

void setup() {

  // Het volgende stuk code is ervoor om de output van vorige uploads te verwijderen.
  while (!Serial) {
    // Wachten op Serial Monitor-verbinding
  }

  // Wacht even om ervoor te zorgen dat de Serial Monitor klaar is
  delay(100);

  // Wis de Serial Monitor-output door een reeks van nieuwe regels te printen
  for (int i = 0; i < 50; i++) {
    Serial.println();
  }


  //initialisatie van de sensoren en de serial monitor.
  Serial.begin(9600);
  lineSensors.initFiveSensors();



  // Wacht op drukken van knop 'A' om de kleur zwart aan te maken
  // en de parameters van waarden waarin deze kleur zich bevindt
  // uit te printen.
  buttonA.waitForButton();
  buzzer.play("L16 ceg>c");
  // Lees de sensorwaarden in
  lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);

  // Kopieer de sensorwaarden naar een nieuw array
  for (int i = 0; i < NUM_SENSORS; i++) {
    copiedSensorValues[i] = lineSensorValues[i];
  }

  Kleur zwart(copiedSensorValues, "zwart");
  zwart.kleurParameters();


  // We gaan nu hetzelfde doen voor de resterende kleuren.
  // kleur Bruin:
  buttonA.waitForButton();
  buzzer.play("L16 ceg>c");
  lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
  for (int i = 0; i < NUM_SENSORS; i++) {
    copiedSensorValues[i] = lineSensorValues[i];
  }

  Kleur bruin(copiedSensorValues, "bruin");
  bruin.kleurParameters();


  // kleur groen:
  buttonA.waitForButton();
  buzzer.play("L16 ceg>c");
  lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
  for (int i = 0; i < NUM_SENSORS; i++) {
    copiedSensorValues[i] = lineSensorValues[i];
  }

  Kleur groen(copiedSensorValues, "groen");
  groen.kleurParameters();



  // kleur: grijs
  buttonA.waitForButton();
  buzzer.play("L16 ceg>c");
  lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
  for (int i = 0; i < NUM_SENSORS; i++) {
    copiedSensorValues[i] = lineSensorValues[i];
  }

  Kleur grijs(copiedSensorValues, "grijs");
  grijs.kleurParameters();
}


void loop() {
}
