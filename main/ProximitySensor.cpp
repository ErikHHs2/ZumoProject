#include "ProximitySensor.h"
#include <Wire.h>
#include <Zumo32U4.h>

/**
 * @brief Functie voor het duwen van een blokje.
 */
void ProximitySensor::duwBlokje() 
{
  // Lees de proximiteitssensoren
  proxSensors.read();

  // Lees de waarden van de linker sensor
  int left_sensor = proxSensors.countsLeftWithLeftLeds();

  // Lees de waarden van de linker-midden sensor
  int center_left_sensor = proxSensors.countsFrontWithLeftLeds();

  // Lees de waarden van de rechter-midden sensor
  int center_right_sensor = proxSensors.countsFrontWithRightLeds();

  // Lees de waarden van de rechter sensor
  int right_sensor = proxSensors.countsRightWithRightLeds();

  // Draai en zoek het blokje met een negatieve snelheid voor de linker motor en een positieve snelheid voor de rechter motor
  motors.setSpeeds(-100, 100);

  // Controleer of de bruinWaardes functie waar is
  if (bruinWaardes()) 
  {
    // Stel de snelheden van de motoren in op 400 om het blokje te duwen
    motors.setSpeeds(400, 400);
  }
}
