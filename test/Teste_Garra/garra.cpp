#include <Arduino.h>
#include <Servo.h>
#include "garra.h"

static Servo servoGarra;

void garra_init(int pino) {
  servoGarra.attach(pino);
  servoGarra.write(0); // inicia aberta
}

void abrirGarra() {
  servoGarra.write(0);
}

void fecharGarra() {
  servoGarra.write(90);
}