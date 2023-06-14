#include <Wire.h>
#include <Zumo32U4.h>

uint16_t maxSpeed = 400;

Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ProximitySensors proxSensors;

int16_t lastError = 0;




#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];
bool useEmitters = true;
unsigned int GroenWaarde[NUM_SENSORS];
unsigned int ZwartWarde[NUM_SENSORS];
unsigned int bruinWaarde[NUM_SENSORS];
// unsigned int WitWarde[NUM_SENSORS];





int GroenMin = 2000;
int GroenMax = 0;
int ZwartMin = 2000;
int ZwartMax = 0;
int WitMax = 0;
int WitMin = 2000;
int bruinMin =2000;
int bruinMax= 0 ;






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













int Groenwaardes(){
  static uint16_t lastSampleTime = 0;

  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();

    // Read the line sensors.
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);
    for (int i = 0; i < 5; i++ ) {
    GroenWaarde[i] = lineSensorValues[i];
    if (GroenMax < GroenWaarde[i]) {
      GroenMax = GroenWaarde[i];
    }else if (GroenMin > GroenWaarde[i]) {
      GroenMin = GroenWaarde[i];
    }
    }
  }
}

int ZwartWardes(){
  static uint16_t lastSampleTime = 0;

  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();

    // Read the line sensors.
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);
    for (int i = 0; i < 5; i++ ) {
    ZwartWarde[i] = lineSensorValues[i];
    if (ZwartMax < ZwartWarde[i]) {
      ZwartMax = ZwartWarde[i];
    }else if (ZwartMin > ZwartWarde[i]) {
      ZwartMin = ZwartWarde[i];
    }
    }
  }

}

int bruinWaardes(){
  static uint16_t lastSampleTime = 0;

  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();

    // Read the line sensors.
    lineSensors.read(lineSensorValues, useEmitters ? QTR_EMITTERS_ON : QTR_EMITTERS_OFF);
    for (int i = 0; i < 5; i++ ) {
    bruinWaarde[i] = lineSensorValues[i];
    if (bruinMax < bruinWaarde[i]) {
      bruinMax = bruinWaarde[i];
    }else if (bruinMin > bruinWaarde[i]) {
      bruinMin = bruinWaarde[i];
    }
    }
  }
}


void setup()
{
  proxSensors.initThreeSensors();
  Serial1.begin(9600);
  lineSensors.initFiveSensors();
  buzzer.play(">g32>>c32");
  buttonA.waitForButton();
  calibrateSensors();
  buttonA.waitForButton();
  Groenwaardes();
  Serial1.print(GroenMax);
  Serial1.print(GroenMin);
  buttonA.waitForButton();
  ZwartWardes();
  buttonA.waitForButton();
  bruinWaardes();
  printReadingsToSerial();
  buzzer.play(">g32>>c32");
  buttonA.waitForButton();
  buzzer.play("L16 cdegreg4");
  while(buzzer.isPlaying());
}

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

void loop()
{
  char xbee = Serial1.read();
  // rijdenZwart();
  // printReadingsToSerial1();
  if((GroenMin - 50) < lineSensorValues[0] && lineSensorValues[0] > (GroenMax + 50) || (GroenMin - 50) < lineSensorValues[1] && lineSensorValues[1] > (GroenMax + 50) || (GroenMin - 50) < lineSensorValues[2] && lineSensorValues[2] > (GroenMax + 50) || (GroenMin - 50) < lineSensorValues[3] && lineSensorValues[3] > (GroenMax + 50) || (GroenMin - 50) < lineSensorValues[4] && lineSensorValues[4] > (GroenMax + 50)) {
      for (int j = 0; j < 5; j++){
        lineSensorValues[j] = lineSensorValues[j] + 100;
      }

    maxSpeed = 400;
    rijdenZwart();
    }
    else if((bruinMin - 50) < lineSensorValues[0] && lineSensorValues[0] > (bruinMin + 50) || (bruinMin - 50) < lineSensorValues[1] && lineSensorValues[1] > (bruinMin + 50) || (bruinMin - 50) < lineSensorValues[2] && lineSensorValues[2] > (bruinMin + 50) || (bruinMin - 50) < lineSensorValues[3] && lineSensorValues[3] > (bruinMin + 50) || (bruinMin - 50) < lineSensorValues[4] && lineSensorValues[4] > (bruinMin + 50)) {
      for (int j = 0; j < 5; j++){
        lineSensorValues[j] = lineSensorValues[j] + 100;
      }

      // --- Read the sensors
      proxSensors.read();    
      int left_sensor = proxSensors.countsLeftWithLeftLeds();
      int center_left_sensor = proxSensors.countsFrontWithLeftLeds();
      int center_right_sensor = proxSensors.countsFrontWithRightLeds();
      int right_sensor = proxSensors.countsRightWithRightLeds();

      // sensor uitlezen op de seriele monitor 
    Serial.println("Left Sensor: " + String(left_sensor));
    Serial.println("voor Left Sensor: " + String(center_left_sensor));
    Serial.println("voor right Sensor: " + String(center_right_sensor));
    Serial.println("right : " + String(right_sensor));
    delay(200);


    //class blokje duwen
      motors.setSpeeds(-100,100);//draai en zoek blok
      if (center_left_sensor && center_right_sensor != 0){
        motors.setSpeeds(400, 400);
        }
      }


    else {
    rijdenZwart();
    maxSpeed = 200;
  }
}




void rijdenZwart(){
int16_t position = lineSensors.readLine(lineSensorValues);

  int16_t error = position - 2000;

  int16_t speedDifference = 10 * error + 50 * (error - lastError);

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
    // printReadingsToSerial1();
  }

  motors.setSpeeds(leftSpeed, rightSpeed);
}



