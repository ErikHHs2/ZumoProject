#include <Wire.h>
#include <Zumo32U4.h>
#include <Arduino.h>


#include "Kleuren.h"
#include "volgLijn.h"

Kleuren kleurtjes;
Zumo32U4LineSensors lineSensors;
volgLijn zwart;

int GroenMin = 2000;
int GroenMax = 0;
int ZwartMin = 2000;
int ZwartMax = 0;
int WitMax = 0;
int WitMin = 2000;
int bruinMin = 2000;
int bruinMax = 0;
bool useEmitters = true;

unsigned int lineSensorValues[NUM_SENSORS];

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  kleurtjes.lineSensors.initFiveSensors();
  zwart.setup();
  kleurtjes.calibrateSensors();
  kleurtjes.Groenwaardes();
  kleurtjes.Groenwaardes();
  kleurtjes.bruinWaardes();

}

void loop() {
  // kleurtjes.ZwartWardes();
  // kleurtjes.printReadingsToSerial1();
  zwart.rijdenZwart();

  if ((GroenMin - 50) < lineSensorValues[0] && lineSensorValues[0] > (GroenMax + 50) || (GroenMin - 50) < lineSensorValues[1] && lineSensorValues[1] > (GroenMax + 50) || (GroenMin - 50) < lineSensorValues[2] && lineSensorValues[2] > (GroenMax + 50) || (GroenMin - 50) < lineSensorValues[3] && lineSensorValues[3] > (GroenMax + 50) || (GroenMin - 50) < lineSensorValues[4] && lineSensorValues[4] > (GroenMax + 50)) {
    for (int j = 0; j < 5; j++) {
      lineSensorValues[j] = lineSensorValues[j] + 100;
    }
    zwart.rijdenZwart();
  } else if ((bruinMin - 50) < lineSensorValues[0] && lineSensorValues[0] > (bruinMin + 50) || (bruinMin - 50) < lineSensorValues[1] && lineSensorValues[1] > (bruinMin + 50) || (bruinMin - 50) < lineSensorValues[2] && lineSensorValues[2] > (bruinMin + 50) || (bruinMin - 50) < lineSensorValues[3] && lineSensorValues[3] > (bruinMin + 50) || (bruinMin - 50) < lineSensorValues[4] && lineSensorValues[4] > (bruinMin + 50)) {
    for (int j = 0; j < 5; j++) {
      lineSensorValues[j] = lineSensorValues[j] + 100;
    }
  }
}
