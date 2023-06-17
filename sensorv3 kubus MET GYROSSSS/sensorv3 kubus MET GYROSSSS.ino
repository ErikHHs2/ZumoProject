#include <Wire.h>
#include <Zumo32U4.h>


Zumo32U4Motors motors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4IMU imu;

char report[120];

void setup() {
  Wire.begin();
  imu.enableDefault();
 Serial.begin(9600);
 if (!imu.init())
  {
    // Failed to detect the compass.
    ledRed(1);
    while(1)
    {
      Serial.println(F("Failed to initialize IMU sensors."));
      delay(100);
    }
  }
  
  char report[120]; 
  void setup();
  proxSensors.initThreeSensors();
  
}

// --- Main program loop
void loop() {


 proxSensors.read();// --- Read the sensors    
  int left_sensor = proxSensors.countsLeftWithLeftLeds();
  int center_left_sensor = proxSensors.countsFrontWithLeftLeds();
  int center_right_sensor = proxSensors.countsFrontWithRightLeds();
  int right_sensor = proxSensors.countsRightWithRightLeds();
  // sensor uitlezen op de seriele monitor 
 Serial.println("Left Sensor: " + String(left_sensor));
 Serial.println("voor Left Sensor: " + String(center_left_sensor));
 Serial.println("voor right Sensor: " + String(center_right_sensor));
 Serial.println("right : " + String(right_sensor));

  imu.read();
  // snprintf_P(report, sizeof(report),
  //   PSTR("A: %6d %6d %6d    M: %6d %6d %6d    G: %6d %6d %6d"),
  //   imu.a.x, imu.a.y, imu.a.z,
  //   imu.m.x, imu.m.y, imu.m.z,
  //   imu.g.x, imu.g.y, imu.g.z);
  // Serial.println(report);
  int acc_x = imu.a.x;
  int acc_y = imu.a.y;
  int acc_z = imu.a.z;
  Serial.println(acc_x);
  Serial.println(acc_y);
  Serial.println(acc_z);

  //   imu.m.x, imu.m.y, imu.m.z,
  //   imu.g.x, imu.g.y, imu.g.z);

  //accelerometer (A), magnetometer (M), and gyroscope (G)
 delay(200);

//class blokje duwen
//motor 2sec naar voren 
  motors.setSpeeds(100,0);
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