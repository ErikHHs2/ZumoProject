#include "Kleuren.h"
#include "LineSensor.h"

Kleuren kleurtjes;
Zumo32U4LineSensors lineSensors;
LineSensor zwart;


void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  kleurtjes.lineSensors.initFiveSensors();
  zwart.setup();
  kleurtjes.calibrateSensors();
  
}

void loop() {
  // kleurtjes.ZwartWardes();
  // kleurtjes.printReadingsToSerial1();
  zwart.rijdenZwart();
  
}
