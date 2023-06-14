/**
 * Titel:
 *    Zumo32U4 Project Groep 2.2
 *
 * Groepsleden:
 *    Erik Bohnet
 *    Vincent Hasper
 *    Boris Horstink
 *    Robin Simons
 *    Jesse Riemens
 *    
 * Datum:
 *    14/06/2023
 * 
 */

#include <Wire.h>
#include <Zumo32U4.h>

// Variabele voor de maximale snelheid van de motoren
uint16_t maxSpeed = 400;

// Objecten voor het regelen van de Zumo32U4
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ProximitySensors proxSensors;

// Variabelen voor het opslaan van de sensorwaarden
unsigned int lineSensorValues[5]; // Waarden van de lijnsensoren
bool useEmitters = true; // Boolean voor het inschakelen van de lijnvolg-emitters
unsigned int GroenWaarde[5]; // Groene waarden van de lijnsensoren
unsigned int ZwartWarde[5]; // Zwarte waarden van de lijnsensoren
unsigned int bruinWaarde[5]; // Bruine waarden van de lijnsensoren

// Variabelen voor het kalibreren van de sensoren
int GroenMin = 2000;
int GroenMax = 0;
int ZwartMin = 2000;
int ZwartMax = 0;
int WitMax = 0;
int WitMin = 2000;
int bruinMin = 2000;
int bruinMax = 0;

/**
 * Kalibreer de sensors van de Zumo-robot.
 */

void calibrateSensors()
{
  delay(1000);
  for (uint16_t i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      motors.setSpeeds(-200, 200); 
    }
    else
    {
      motors.setSpeeds(200, -200); 
    }
    lineSensors.calibrate(); // Kalibreer de lijnsensoren
  }
  motors.setSpeeds(0, 0); // Stop de motoren
}

/**
 * Lees de groenwaarden van de lijnsensoren.
 */

void Groenwaardes()
{
  static uint16_t lastSampleTime = 0;
  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);
    for (int i = 0; i < 5; i++)
    {
      GroenWaarde[i] = lineSensorValues[i];
      if (GroenMax < GroenWaarde[i])
      {
        GroenMax = GroenWaarde[i];
      }
      else if (GroenMin > GroenWaarde[i])
      {
        GroenMin = GroenWaarde[i];
      }
    }
  }
}

/**
 * Lees de zwartwaarden van de lijnsensoren.
 */

void ZwartWardes()
{
  static uint16_t lastSampleTime = 0;
  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);
    for (int i = 0; i < 5; i++)
    {
      ZwartWarde[i] = lineSensorValues[i];
      if (ZwartMax < ZwartWarde[i])
      {
        ZwartMax = ZwartWarde[i];
      }
      else if (ZwartMin > ZwartWarde[i])
      {
        ZwartMin = ZwartWarde[i];
      }
    }
  }
}

/**
 * Lees de bruinwaarden van de lijnsensoren.
 */

void bruinWaardes()
{
  static uint16_t lastSampleTime = 0;
  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);
    for (int i = 0; i < 5; i++)
    {
      bruinWaarde[i] = lineSensorValues[i];
      if (bruinMax < bruinWaarde[i])
      {
        bruinMax = bruinWaarde[i];
      }
      else if (bruinMin > bruinWaarde[i])
      {
        bruinMin = bruinWaarde[i];
      }
    }
  }
}

/**
 * Initialiseer de Zumo-robot en voer de kalibratie uit.
 */

void setup()
{
  proxSensors.initThreeSensors(); // Initialisatie van de proximitysensoren
  Serial1.begin(9600); // Initialisatie van seriële communicatie
  lineSensors.initFiveSensors(); // Initialisatie van de lijnsensoren
  buttonA.waitForButton(); // Wacht op drukken van knop A
  calibrateSensors(); // Kalibreer de sensoren
  buttonA.waitForButton(); // Wacht op drukken van knop A
  Groenwaardes(); // Lees de groene waarden van de sensoren
  Serial1.print(GroenMax); // Stuur de maximale groene waarde via seriële communicatie
  Serial1.print(GroenMin); // Stuur de minimale groene waarde via seriële communicatie
  buttonA.waitForButton(); // Wacht op drukken van knop A
  ZwartWardes(); // Lees de zwarte waarden van de sensoren
  buttonA.waitForButton(); // Wacht op drukken van knop A
  bruinWaardes(); // Lees de bruine waarden van de sensoren
  printReadingsToSerial(); // Print de sensorwaarden naar de seriële monitor
  buttonA.waitForButton(); // Wacht op drukken van knop A
}

/**
 * Print de groenwaarden naar de seriële monitor.
 */

void printReadingsToSerial()
{
  char buffer[800];
  sprintf(buffer, "%4d %4d %4d %4d %4d %c\n",
    GroenWaarde[0],
    GroenWaarde[1],
    GroenWaarde[2],
    GroenWaarde[3],
    GroenWaarde[4],
    useEmitters ? 'E' : 'e'
  );
  Serial1.print(buffer);
}

/**
 * Print de lijnwaarden naar de seriële monitor.
 */

// Functie voor het printen van de sensorwaarden naar de seriële monitor
void printReadingsToSerial1()
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
  Serial1.print(buffer);
}

/**
 * Het hoofdprogramma van de Zumo-robot.
 */

// Hoofdprogramma wordt continue uitgevoerd
void loop()
{
  char xbee = Serial1.read(); // Lees een karakter van de seriële communicatie
  // Controleer de sensorwaarden en voer de bijbehorende acties uit
  if ((GroenMin - 50) < lineSensorValues[0] && lineSensorValues[0] > (GroenMax + 50) || 
      (GroenMin - 50) < lineSensorValues[1] && lineSensorValues[1] > (GroenMax + 50) || 
      (GroenMin - 50) < lineSensorValues[2] && lineSensorValues[2] > (GroenMax + 50) || 
      (GroenMin - 50) < lineSensorValues[3] && lineSensorValues[3] > (GroenMax + 50) || 
      (GroenMin - 50) < lineSensorValues[4] && lineSensorValues[4] > (GroenMax + 50)) 
  {
    for (int j = 0; j < 5; j++)
    {
      lineSensorValues[j] = lineSensorValues[j] + 100;
    }
    maxSpeed = 400;
    rijdenZwart(); // Rijd op de zwarte lijn
  }
  else if ((bruinMin - 50) < lineSensorValues[0] && lineSensorValues[0] > (bruinMin + 50) || 
           (bruinMin - 50) < lineSensorValues[1] && lineSensorValues[1] > (bruinMin + 50) || 
           (bruinMin - 50) < lineSensorValues[2] && lineSensorValues[2] > (bruinMin + 50) || 
           (bruinMin - 50) < lineSensorValues[3] && lineSensorValues[3] > (bruinMin + 50) || 
           (bruinMin - 50) < lineSensorValues[4] && lineSensorValues[4] > (bruinMin + 50)) 
  {
    for (int j = 0; j < 5; j++)
    {
      lineSensorValues[j] = lineSensorValues[j] + 100;
    }
    proxSensors.read();
    int left_sensor = proxSensors.countsLeftWithLeftLeds();
    int center_left_sensor = proxSensors.countsFrontWithLeftLeds();
    int center_right_sensor = proxSensors.countsFrontWithRightLeds();
    int right_sensor = proxSensors.countsRightWithRightLeds();

    Serial.println("Left Sensor: " + String(left_sensor));
    Serial.println("voor Left Sensor: " + String(center_left_sensor));
    Serial.println("voor right Sensor: " + String(center_right_sensor));
    Serial.println("right : " + String(right_sensor));
    delay(200);

    motors.setSpeeds(-100, 100);
    if (center_left_sensor && center_right_sensor != 0)
    {
      motors.setSpeeds(400, 400);
    }
  }
  else
  {
    rijdenZwart(); // Rijd op de zwarte lijn
    maxSpeed = 200;
  }
}

/**
 * Rijdt op een zwarte lijn.
 */

void rijdenZwart()
{
  // Lees de sensorwaarden
  lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);

  // Bereken de verschilwaarden voor de motorinstellingen
  int32_t difference = 0;
  int32_t sum = 0;
  for (uint8_t i = 0; i < 5; i++)
  {
    int32_t value = lineSensorValues[i];
    value = map(value, ZwartMin, ZwartMax, 0, 1000);
    if (value < 0)
      value = 0;
    if (value > 1000)
      value = 1000;
    sum += value * (i * 4 - 10);
    difference += value;
  }

  // Corrigeer de motorinstellingen op basis van de verschilwaarden
  int32_t error = sum / difference;
  int32_t speedDifference = error / 4;
  int32_t leftSpeed = maxSpeed + speedDifference;
  int32_t rightSpeed = maxSpeed - speedDifference;

  // Stel de motorinstellingen in
  motors.setSpeeds(leftSpeed, rightSpeed);
}
