#include <Zumo32U4.h>
#include "LineSensor.h"


LineSensor lineSensor;

void setup() {
  
  // in deze code worden de linesensoren geinitialiseerd, om ze vervolgens te kunnen gebruiken.
  lineSensor.initialize();
  
  
  lineSensor.calibrate();
  
  
  Serial.begin(9600);
}

void loop() {
 
  for (uint8_t i = 0; i < 5; i++) {
    uint16_t sensorValue = lineSensor.readSensor(i);
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(sensorValue);
  }
  
 
  delay(100);
}
