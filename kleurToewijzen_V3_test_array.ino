#include <Wire.h>
#include <Zumo32U4.h>

const uint16_t maxSpeed = 400;
Zumo32U4LineSensors lineSensors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];
unsigned int copiedSensorValues[NUM_SENSORS];

void setup()
{
  Serial.begin(9600);
  lineSensors.initFiveSensors();

  // Wacht op drukken van knop 'A'

  Serial.print(F("Press A"));

  Serial.print(F("to read"));
  buttonA.waitForButton();
  
  // Lees de sensorwaarden in
  lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
  
  // Kopieer de sensorwaarden naar een nieuw array
  for (int i = 0; i < NUM_SENSORS; i++) {
    copiedSensorValues[i] = lineSensorValues[i];
  }

  // Print de gekopieerde sensorwaarden
  Serial.println("/n Copied Sensor Values:");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.println(copiedSensorValues[i]);
    Serial.println(" ");
  }
}

void loop()
{
  // Voer hier de hoofdfunctionaliteit uit
}
