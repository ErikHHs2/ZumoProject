#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4ProximitySensors sensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;

void setup()
{
  buttonA.waitForButton();

  delay(1000);

  sensors.initThreeSensors();
  motors.setSpeeds(200, 200);
}

void loop()
{
  sensors.read();

  if (sensors.countsFrontWithLeftLeds() + sensors.countsFrontWithRightLeds() > 0)
  {
    motors.setSpeeds(-200, 200);
    delay(500);
  }
  else
  {
    motors.setSpeeds(200, 200);
  }
}
 