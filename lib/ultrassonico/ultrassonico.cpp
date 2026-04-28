#include <Arduino.h>
#include "ultrassonico.h"

// Variáveis globais do módulo
int t, e;
int TIME_OUT = 30000;  // Timeout em microsegundos (~30ms) - evita travamento

/**
 * Inicializa sensor ultrassônico
 * @param trig Pino que envia pulso (OUTPUT)
 * @param echo Pino que recebe resposta (INPUT)
 */
void ultra_init(int trig, int echo) {
  t = trig;
  e = echo;

  pinMode(t, OUTPUT);
  pinMode(e, INPUT);
}

/**
 * Lê distância até obstáculo mais próximo
 * 
 * Protocolo:
 *   1. Manda pulso de 10µs no trigger
 *   2. Aguarda pulso retornar no echo
 *   3. Calcula distancia = (tempo × velocidade som) / 2
 * 
 * @return Distância em cm. Retorna 999.0 se timeout (sem obstáculo ou sensor falho)
 */
float lerDistancia() {
  // Prepara novo pulso
  digitalWrite(t, LOW);
  delayMicroseconds(2);
  digitalWrite(t, HIGH);
  delayMicroseconds(10);  // Pulso de 10µs
  digitalWrite(t, LOW);

  // Aguarda e mede duração do eco
  long duracao = pulseIn(e, HIGH, TIME_OUT);
  
  if (duracao == 0) {
    // Timeout: nenhuma resposta ou sensor falho
    return 999.0;
  }

  // Cálculo: tempo * velocidade som / ida-volta
  // 0.034 cm/µs = velocidade som no ar
  // / 2.0 porque o som vai e volta
  return duracao * 0.034 / 2.0;
}