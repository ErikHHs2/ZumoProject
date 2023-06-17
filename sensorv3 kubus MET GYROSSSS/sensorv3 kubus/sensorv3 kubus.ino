#include <Zumo32U4.h>


using namespace std;

Zumo32U4Motors motors;
Zumo32U4ProximitySensors proxSensors;


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

  // sensor uitlezen op de seriele monitor 
 Serial.println("Left Sensor: " + String(left_sensor));
 Serial.println("voor Left Sensor: " + String(center_left_sensor));
 Serial.println("voor right Sensor: " + String(center_right_sensor));
 Serial.println("right : " + String(right_sensor));
 delay(200);


//class blokje duwen
  motors.setSpeeds(100,0);//draai en zoek blok
  if (center_left_sensor && center_right_sensor > 2){
    motors.setSpeeds(100, 100);
  }
  
  


    //if (groenwaarden vind set )
    //
    //delay(1900);
    //motors.setSpeeds(0, 20);
   
 
 

   
      //if (center_left_sensor>1){
      //motors.setSpeeds(0, 0);
      //delay(1900);
      //motors.setSpeeds(100,100);
    
    
 
 
}