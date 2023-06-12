
#include <Wire.h>
#include <Zumo32U4.h>

const uint16_t maxSpeed = 200;


Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;
Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;

int16_t lastError = 0;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];

//added om de lijnsensoren in te schakelen.
bool useEmitters = true;

//Added om waardes van de lijnsensor binnen te krijgen en te printen op de terminal.
void printReadingsToSerial()
{
  char buffer[80];
  sprintf(buffer, "%4d %4d %4d %4d %4d %c\n",
          lineSensorValues[0],
          lineSensorValues[1],
          lineSensorValues[2],
          lineSensorValues[3],
          lineSensorValues[4],
          useEmitters ? 'E' : 'e'
         );
  Serial.print(buffer);
}


void setup()
{
  Serial.begin(9600);

  lineSensors.initFiveSensors();


  //speel geluid af en begin met uitlezen
  buttonA.waitForButton();

  buzzer.play("L16 ceg>c");

}



void loop()
{
  //  // Read the line sensors.
  lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);
  
//
//  if ((lineSensorValues[0] > 500) && (lineSensorValues[0] < 1000)&&(lineSensorValues[4] > 500) && (lineSensorValues[4] < 1000)) {
//    motors.setSpeeds(0, 0);
//    delay(5000);
//    motors.setSpeeds(200, 200);
//    delay(2000);
//  }
//
//  //grijze lijn links? draai bij het zien van zwarte kruising naar links.
//  if (lineSensorValues[0] >500 && <1000){
//    motors.setSpeeds(150, 150);
//    if ((lineSensorValues[0] > 999) && (lineSensorValues[4] > 999){
//      motors.setSpeeds(0, 150);
//      delay(2000);
//    }
//  }
//  //grijze lijn rechts? draai bij het zien van zwarte kruising naar rechts.
//
//  if (lineSensorValues[4] >500 && <1000){
//    motors.setSpeeds(150, 150);
//    if ((lineSensorValues[0] > 999) && (lineSensorValues[4] > 999){
//      motors.setSpeeds(150, 0);
//      delay(2000);
//    }
//  }
//
//    //motoren gaan draaien op halve snelheid wanneer er een groene lijn wordt gedetecteerd.
//    if (lineSensorValues[1] > 200 && lineSensorValues[1] < 425 || lineSensorValues[2] > 200 && lineSensorValues[2] < 425 || lineSensorValues[3] > 200 && lineSensorValues[3] < 425){
//        motors.setSpeeds(100, 100);
//  }
//
//  Hier wordt de functie die het blokje uit de cirkel moet duwen aangeroepen als er een bruine lijn , deze is nog niet definitief dus vandaar staat deze code in commentaar.
//  if ((lineSensorValues[1] || lineSensorValues[2] || lineSensorValues[3]) > 425 && < 900){
//    blokjeDuwen.blokjeDuwen();
//  }
//
//  if ((lineSensorValues[1] || lineSensorValues[2] || lineSensorValues[3]) > 999) {
//    motors.setSpeeds(200,200);
//  }




  printReadingsToSerial();


  //De volgende code bepaald de positie van de lijn in de font files.
  int16_t position = lineSensors.readLine(lineSensorValues);

                     delay(200);
}
