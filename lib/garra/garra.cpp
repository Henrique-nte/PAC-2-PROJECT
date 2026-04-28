#include <Arduino.h>
#include <Servo.h>
#include "garra.h"

// Constantes de ângulo - AJUSTE CONFORME TESTES FÍSICOS
const int ANGULO_GARRA_ABERTA = 0;    // Garra aberta (0°)
const int ANGULO_GARRA_FECHADA = 90;  // Garra fechada (90°) - ajuste conforme necessário

// Objeto Servo
Servo servo;

/**
 * Inicializa servo na posição aberta
 * @param pino Pino PWM do servo (3, 5, 6, 9, 10, 11 em Arduino Uno)
 */
void garra_init(int pino) {
  servo.attach(pino);
  servo.write(0);  // Posição inicial segura
}

/**
 * Abre a garra
 */
void abrirGarra() {
  servo.write(ANGULO_GARRA_ABERTA);
}

/**
 * Fecha a garra
 */
void fecharGarra() {
  servo.write(ANGULO_GARRA_FECHADA);
}