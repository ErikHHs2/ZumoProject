#include "ProximitySensor.h"
#include <Wire.h>
#include <Zumo32U4.h>

void ProximitySensor::duwBlokje() {


  proxSensors.read();
  int left_sensor = proxSensors.countsLeftWithLeftLeds();
  int center_left_sensor = proxSensors.countsFrontWithLeftLeds();
  int center_right_sensor = proxSensors.countsFrontWithRightLeds();
  int right_sensor = proxSensors.countsRightWithRightLeds();


  motors.setSpeeds(-100,100);//draai en zoek blok
      if (bruinWaardes()){
        motors.setSpeeds(400, 400);
        }
      }


