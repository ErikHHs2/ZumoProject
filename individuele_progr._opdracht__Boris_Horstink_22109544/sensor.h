#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

void setup() {
  lineSensors.initThreeSensors();
}

void loop() {
  unsigned int sensors = lineSensors.read();

  // Lijnvolging voor een zwarte lijn
  if (lineSensors.lineSensor(1) && lineSensors.lineSensor(2) && lineSensors.lineSensor(3)) {
    motors.setSpeeds(200, 200); // Beide motoren vooruit op volle snelheid
  }
  else {
    // Lijnvolging voor een groene lijn op halve snelheid
    if (lineSensors.lineSensor(1) && !lineSensors.lineSensor(2) && lineSensors.lineSensor(3)) {
      motors.setSpeeds(100, 100); // Beide motoren vooruit op halve snelheid
    }
    // Volg de richting van een grijze lijn
    else if (!lineSensors.lineSensor(1) && lineSensors.lineSensor(2) && !lineSensors.lineSensor(3)) {
      motors.setSpeeds(-100, 100); // Draai naar links
    }
    else if (!lineSensors.lineSensor(1) && !lineSensors.lineSensor(2) && lineSensors.lineSensor(3)) {
      motors.setSpeeds(100, -100); // Draai naar rechts
    }
    else {
      motors.setSpeeds(0, 0); // Stop als de lijn niet wordt gedetecteerd
    }
  }
}
