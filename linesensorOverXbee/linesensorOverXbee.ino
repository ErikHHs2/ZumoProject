#include <Wire.h>
#include <Zumo32U4.h>


const uint16_t maxSpeed = 0;

Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;

int16_t lastError = 0;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];
bool useEmitters = true;


void calibrateSensors()
{
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
  motors.setSpeeds(0, 0);
}



void setup()
{
  Serial1.begin(9600);
  lineSensors.initFiveSensors();

  buzzer.play(">g32>>c32");

  buttonA.waitForButton();


  calibrateSensors();

  buttonA.waitForButton();

  buzzer.play("L16 cdegreg4");
  while(buzzer.isPlaying());
}

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
  Serial1.print(buffer);
}

void loop()
{
  int16_t position = lineSensors.readLine(lineSensorValues);

  int16_t error = position - 2000;

  int16_t speedDifference = error / 4 + 6 * (error - lastError);

  lastError = error;

  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  static uint16_t lastSampleTime = 0;

  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();

    // Read the line sensors.
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);

    // Send the results to the display and to the serial monitor.
    printReadingsToSerial();
  }

  motors.setSpeeds(leftSpeed, rightSpeed);
}