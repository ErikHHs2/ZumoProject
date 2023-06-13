
#include "Kleur.h"

Kleur::Kleur(unsigned int waarden[], const char* naam) {
  // Kopieer de waarden naar de datamember array
  for (int i = 0; i < 5; i++) {
    sensorWaarden[i] = waarden[i];
  }

  // Bereken de laagste en hoogste waarde van het array
  laagsteWaarde = sensorWaarden[0];
  hoogsteWaarde = sensorWaarden[0];
  
  for (int i = 1; i < 5; i++) {
    if (sensorWaarden[i] < laagsteWaarde) {
      laagsteWaarde = sensorWaarden[i];
    }
    if (sensorWaarden[i] > hoogsteWaarde) {
      hoogsteWaarde = sensorWaarden[i];
    }
  }

  // Sla de naam van het object op
  kleurNaam = naam;
}


void Kleur::kleurParameters() {
  Serial.print(kleurNaam);
  Serial.print(" - Hoogste waarde: ");
  Serial.print(hoogsteWaarde);
  Serial.print(", Laagste waarde: ");
  Serial.println(laagsteWaarde);
}