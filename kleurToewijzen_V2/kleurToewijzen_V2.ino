
#include "Kleur.h"
#include <Zumo32U4.h>

Zumo32U4Buzzer buzzer;
Zumo32U4ButtonA buttonA;
Zumo32U4LineSensors lineSensors;


#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];

bool useEmitters = true;

// Kleur zwart;
// Kleur groen;
// Kleur bruin;
// Kleur grijs;

void setup() 
{
  // Initialize the serial communication
    Serial.begin(9600);
    lineSensors.initFiveSensors();

  // Initialize the serial communication

  
  buttonA.waitForButton();
  buzzer.play("L16 ceg>c");

  lineSensors.readLine(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);

  int sensors[5] = lineSensors.readLine(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);

  Kleur zwart(lineSensorValues);

  // Read the sensor values
  zwart.readSensors();

  // Get the minimum and maximum values
  int minValue = zwart.getMinimumValue();
  int maxValue = zwart.getMaximumValue();

  // Send the values to the serial monitor
  Serial.print("Minimum Value zwart: ");
  Serial.println(minValue);
  Serial.print("Maximum Value zwart: ");
  Serial.println(maxValue);
}

void loop()  
{


}
