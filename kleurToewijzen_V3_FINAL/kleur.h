#include <Arduino.h> //voor Serial
#ifndef KLEUR_H
#define KLEUR_H

class Kleur {
private:
  unsigned int sensorWaarden[5];  
  unsigned int laagsteWaarde;     
  unsigned int hoogsteWaarde;     
  const char* kleurNaam;         

public:
  Kleur(unsigned int waarden[], const char* naam);
  void kleurParameters();

};

#endif