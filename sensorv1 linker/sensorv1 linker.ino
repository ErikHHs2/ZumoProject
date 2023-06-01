#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4ProximitySensors proxSensors;

// --- Setup function
void setup() {
  // Get the proximity sensors initialized
  proxSensors.initThreeSensors();
}

// --- Main program loop
void loop() {

  // --- Read the sensors
  proxSensors.read();    
  int left_sensor = proxSensors.countsLeftWithLeftLeds();
  int center_left_sensor = proxSensors.countsFrontWithLeftLeds();
  int center_right_sensor = proxSensors.countsFrontWithRightLeds();
  int right_sensor = proxSensors.countsRightWithRightLeds();

 Serial.println("Left Sensor: " + String(left_sensor));
 delay(500);

 Serial.println("voor Left Sensor: " + String(center_left_sensor));
 delay(500);
 
 // hiermee kan je met data van de linker sensor een bocht maken 
 //if (left_sensor >5){
 //   motors.setSpeeds(200, 0);
 //  delay(1000);
//  motors.setSpeeds(0, 0);
    
 
 if (center_left_sensor >6){
    motors.setSpeeds(200, 0);
    delay(1900);
    motors.setSpeeds(0, 0);
    
 }
 
}