#include "ultrassonico.h"
#include "../include/pinos.h"

#include "Arduino.h"

void setup() {
  ultra_init(PINO_TRIG, PINO_ECHO);
}

void loop() {
  float distancia = lerDistancia();
  delay(300);
}