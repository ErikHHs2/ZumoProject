

#include <Wire.h>
#include <Zumo32U4.h>


const uint16_t maxSpeed = 250;

Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA; 


int16_t lastError = 0;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];

//added om de lijnsensoren in te schakelen.
bool useEmitters = true;


void calibrateSensors()
{
  
  //Wacht 1 seconden en begin dan sensor calibratie door naar links en rechts te draaien.
  delay(1000);
  for(uint16_t i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200, -200);
    }

    lineSensors.calibrate();
  }
    {
      motors.setSpeeds(0, 0);
    }
}





void setup()
{
  Serial.begin(9600);

  lineSensors.initFiveSensors();

  
  buzzer.play(">g32>>c32");

  
  //Na het inklikken van button A zal methode calibrateSensors() worden aangeroepen,
  //deze methode zal eerst de zumo naar links en rechts laten draaien zodat er onderscheid kan worden gemaakt waar er een zwarte lijn is en waar niet.
  //Direct hierna begint de Zumo de gedecteerde lijn te volgen.
  buttonA.waitForButton();

  calibrateSensors();

  
  buzzer.play("L16 cdegreg4");
  while(buzzer.isPlaying());
}


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

void loop()
{
  //De volgende code bepaald de positie van de lijn in de font files.
  int16_t position = lineSensors.readLine(lineSensorValues);

  printReadingsToSerial();

//stop motoren wanneer grijze streep wordt bereikt.
  if ((lineSensorValues[0] > 500) && (lineSensorValues[0] < 1000)&&(lineSensorValues[4] > 500) && (lineSensorValues[4] < 1000)) {
    motors.setSpeeds(0, 0);
    delay(5000);
    motors.setSpeeds(200, 200);
    delay(2000);
  }

//  //grijze lijn links? draai bij het zien van zwarte kruising naar links.
//  if (lineSensorValues[0] >500 && lineSensorValues[0] <1000){
//    motors.setSpeeds(150, 150);
//    if (lineSensorValues[0] > 999 && lineSensorValues[4] > 999){
//      motors.setSpeeds(0, 150);
//      delay(2000);
//    }
//  }
//  //grijze lijn rechts? draai bij het zien van zwarte kruising naar rechts.
//
//  if (lineSensorValues[4] >500 && lineSensorValues[4] <1000){
//    motors.setSpeeds(150, 150);
//    if (lineSensorValues[0] > 999 && lineSensorValues[4] > 999){
//      motors.setSpeeds(150, 0);
//      delay(2000);
//    }
//  }

    //motoren gaan draaien op halve snelheid wanneer er een groene lijn wordt gedetecteerd.
    if (lineSensorValues[1] > 200 && lineSensorValues[1] < 425 || lineSensorValues[2] > 200 && lineSensorValues[2] < 425 || lineSensorValues[3] > 200 && lineSensorValues[3] < 425){
        motors.setSpeeds(100, 100);
  }

//  Hier wordt de functie die het blokje uit de cirkel moet duwen aangeroepen als er een bruine lijn , deze is nog niet definitief dus vandaar staat deze code in commentaar.
//  if ((lineSensorValues[1] || lineSensorValues[2] || lineSensorValues[3]) > 425 && < 900){
//    blokjeDuwen.blokjeDuwen();
//  }

//  if ((lineSensorValues[1] > 999 || lineSensorValues[2] > 999 || lineSensorValues[3]) > 999) {
//    motors.setSpeeds(200,200);
//  }
else{
  
  //Hier staat beschreven hoe de Zumo kan zien hoe ver deze is verwijders van de lijn.
  int16_t error = position - 2000;

  //Deze codefragment verwijst naar een Proportional-Integral-Derivative (PID) regelsysteem voor lijnvolging
  //met behulp van een Zumo-robot. Het PID-regelsysteem gebruikt feedback van een sensor om de
  //snelheidsverschillen tussen de motoren te regelen, gebaseerd op de proportionele en afgeleide termen van het systeem.
  //De integrale term wordt over het algemeen niet erg nuttig geacht voor lijnvolging.
  //In deze specifieke codefragment wordt een proportionele constante van 1/4 en een afgeleide constante van 6 gebruikt,
  //wat redelijk goed zou moeten werken voor veel Zumo-motoren. 
  //Het is waarschijnlijk verstandig om deze constanten op basis van trial-and-error
  //af te stemmen op de specifieke Zumo en lijnbaan.
  int16_t speedDifference = error / 4 + 6 * (error - lastError);

  lastError = error;

  //Deze code zorgt ervoor dat de zumo zijn individuele motoren 
  //kan laten bijsturen als ze onregelmatige snelheden vertonen.
  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;


  motors.setSpeeds(200, 200);
}
}
