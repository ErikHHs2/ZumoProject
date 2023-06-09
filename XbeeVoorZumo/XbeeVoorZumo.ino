

#include <Zumo32U4.h> // Importeer de Zumo32U4 bibliotheek die nodig is om de motoren van de robot aan te sturen

Zumo32U4Motors motors; // Maak een object van de klasse Zumo32U4Motors aan om de motoren van de robot aan te sturen

void setup() {
  Serial1.begin(9600); // Start de seriële communicatie op een baudrate van 9600
  motors.setSpeeds(0, 0); // Stel de motorsnelheden in op 0 (stilstaand)
}

void loop() {
  if (Serial1.available()) { // Controleer of er data beschikbaar is op de seriële communicatie poort
    char xbee = Serial1.read(); // Lees de ontvangen data van de seriële communicatie poort
    if (xbee == 'w') { // Als de ontvangen data 'w' is, beweeg de robot vooruit
      motors.setSpeeds(200, 200);
    }
    else if (xbee == 'd') { // Als de ontvangen data 'd' is, draai de robot naar rechts
      motors.setSpeeds(200, -200);
    }
    else if (xbee == 'a') { // Als de ontvangen data 'a' is, draai de robot naar links
      motors.setSpeeds(-200, 200);
    }
    else if (xbee == 's') { // Als de ontvangen data 's' is, beweeg de robot achteruit
      motors.setSpeeds(-200, -200);
    }
    else if (xbee == 'b') { // Als de ontvangen data 'b' is, verhoog de snelheid van de robot
      motors.setSpeeds(400, 400);
    }
    else if (xbee == 't') { // Als de ontvangen data 't' is, verhoogt de snelheid van de robot als die achteruit gaat
      motors.setSpeeds(-400, -400);
    }
    else { // Als de ontvangen data iets anders is, stop de robot
      motors.setSpeeds(0,0);
    }
  }
}


