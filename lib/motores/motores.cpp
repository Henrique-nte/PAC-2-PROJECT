#include <Arduino.h>
#include "motores.h"

// Variáveis globais do módulo
int mEA, mER, mDA, mDR;

/**
 * Inicializa todos os pinos dos motores como saída
 * IMPORTANTE: Arduino não fornece controle PWM por padrão neste código
 *             Se precisar velocidade variável, use analogWrite() nos pinos PWM
 * 
 * @param eA Pino esquerdo - avanço
 * @param eR Pino esquerdo - recua
 * @param dA Pino direito - avanço
 * @param dR Pino direito - recua
 */
void motores_init(int eA, int eR, int dA, int dR) {
  mEA = eA;
  mER = eR;
  mDA = dA;
  mDR = dR;

  pinMode(mEA, OUTPUT);
  pinMode(mER, OUTPUT);
  pinMode(mDA, OUTPUT);
  pinMode(mDR, OUTPUT);
}

/**
 * Para ambos os motores
 * Reset seguro: desativa todos os pinos
 */
void pararMotores() {
  digitalWrite(mEA, LOW);
  digitalWrite(mER, LOW);
  digitalWrite(mDA, LOW);
  digitalWrite(mDR, LOW);
}

/**
 * Ambos motores avançam = movimento reto para frente
 */
void andarFrente() {
  digitalWrite(mEA, HIGH);
  digitalWrite(mER, LOW);
  digitalWrite(mDA, HIGH);
  digitalWrite(mDR, LOW);
}

/**
 * Ambos motores recuam = movimento reto para trás
 */
void andarRe() {
  digitalWrite(mEA, LOW);
  digitalWrite(mER, HIGH);
  digitalWrite(mDA, LOW);
  digitalWrite(mDR, HIGH);
}

/**
 * Curva suave à esquerda
 * Motor direito avança, esquerdo para
 * Cria raio maior de curvatura (ideal para seguir linha)
 */
void curvaEsquerda() {
  // Motor esquerdo: para
  digitalWrite(mEA, LOW);
  digitalWrite(mER, LOW);   // Reset completo - garante sem conflito
  // Motor direito: avança
  digitalWrite(mDA, HIGH);
  digitalWrite(mDR, LOW);   // Reset completo
}

/**
 * Curva suave à direita
 * Motor esquerdo avança, direito para
 */
void curvaDireita() {
  // Motor esquerdo: avança
  digitalWrite(mEA, HIGH);
  digitalWrite(mER, LOW);   // Reset completo
  // Motor direito: para
  digitalWrite(mDA, LOW);
  digitalWrite(mDR, LOW);   // Reset completo
}

/**
 * Rotação aguda para esquerda
 * Motor direito frente + motor esquerdo ré
 */
void virarEsquerda() {
  digitalWrite(mEA, LOW);
  digitalWrite(mER, HIGH);
  digitalWrite(mDA, HIGH);
  digitalWrite(mDR, LOW);
}

/**
 * Rotação aguda para direita
 * Motor esquerdo frente + motor direito ré
 */
void virarDireita() {
  digitalWrite(mEA, HIGH);
  digitalWrite(mER, LOW);
  digitalWrite(mDA, LOW);
  digitalWrite(mDR, HIGH);
}