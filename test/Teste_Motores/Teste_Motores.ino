#include "motores.h"
#include "../include/pinos.h"

#include "Arduino.h"

void setup() {
  motores_init(MOTOR_ESQ_AVANCA, MOTOR_ESQ_RECUA, MOTOR_DIR_AVANCA, MOTOR_DIR_RECUA);
  pararMotores();
  delay(1000);
}

void loop() {
  andarFrente();
  delay(2000);
  pararMotores();
  delay(1000);

  andarRe();
  delay(2000);
  pararMotores();
  delay(1000);

  curvaEsquerda();
  delay(2000);
  pararMotores();
  delay(1000);

  curvaDireita();
  delay(2000);
  pararMotores();
  delay(1000);

  virarEsquerda();
  delay(2000);
  pararMotores();
  delay(1000);

  virarDireita();
  delay(2000);
  pararMotores();
  delay(2000);
}