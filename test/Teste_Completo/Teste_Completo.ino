#include "../lib/motores/motores.h"
#include "../lib/sensoresLinha/sensoresLinha.h"
#include "../lib/ultrassonico/ultrassonico.h"
#include "../lib/garra/garra.h"
#include "../include/pinos.h"

#include "Arduino.h"

Garra garra;

enum Movimento {
  FRENTE,
  ESQ,
  DIR,
  PARADO
};

void setup() {
  motores_init(MOTOR_ESQ_AVANCA, MOTOR_ESQ_RECUA, MOTOR_DIR_AVANCA, MOTOR_DIR_RECUA);
  sensores_init(PINO_ESQ_EXT, PINO_ESQ_INT, PINO_DIR_INT, PINO_DIR_EXT);
  ultra_init(PINO_TRIG, PINO_ECHO);
  garra.begin(PINO_SERVO);
}

Movimento calcular(bool eExt, bool eInt, bool dInt, bool dExt) {
  if (eInt && dInt) return FRENTE;
  if (eExt) return ESQ;
  if (dExt) return DIR;
  return PARADO;
}

void loop() {
  garra.update();

  bool eExt, eInt, dInt, dExt;
  lerSensores(eExt, eInt, dInt, dExt);

  Movimento m = calcular(eExt, eInt, dInt, dExt);

  switch (m) {
    case FRENTE: andarFrente(); break;
    case ESQ: curvaEsquerda(); break;
    case DIR: curvaDireita(); break;
    case PARADO: pararMotores(); break;
  }
}