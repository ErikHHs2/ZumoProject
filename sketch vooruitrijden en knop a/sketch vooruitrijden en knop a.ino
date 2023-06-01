#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4ProximitySensors sensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;



void setup()
{
  
  buttonA.waitForButton();

  delay(1000);


  motors.setSpeeds(400, 400);
}

void loop()
{
 
}
 
 