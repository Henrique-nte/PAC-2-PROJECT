#include <Arduino.h>
#include "sensoresLinha.h"

// Variáveis globais do módulo
int sEE, sEI, sDI, sDE;

/**
 * Inicializa todos os 4 sensores de linha
 * INPUT_PULLUP = resistor interno ativado
 * 
 * @param eExt Pino do sensor esquerda externa
 * @param eInt Pino do sensor esquerda interna
 * @param dInt Pino do sensor direita interna
 * @param dExt Pino do sensor direita externa
 */
void sensores_init(int eExt, int eInt, int dInt, int dExt) {
  sEE = eExt;
  sEI = eInt;
  sDI = dInt;
  sDE = dExt;

  pinMode(sEE, INPUT_PULLUP);
  pinMode(sEI, INPUT_PULLUP);
  pinMode(sDI, INPUT_PULLUP);
  pinMode(sDE, INPUT_PULLUP);
}

/**
 * Lê valor de um sensor individual
 * @param pino Pino do sensor
 * @return true se detecta linha (LOW), false se vê branco (HIGH)
 * 
 * Convenção: Invertida! digitalRead(LOW) → true
 * Porque sensor IR retorna LOW quando vê preto (absorve luz)
 */
bool ler(int pino) {
  return digitalRead(pino) == LOW;  // Inverte a lógica
}

/**
 * Lê estado de todos os 4 sensores de uma vez
 * Chamado continuamente no loop() para atualizar estado
 */
void lerSensores(bool &eExt, bool &eInt, bool &dInt, bool &dExt) {
  eExt = ler(sEE);
  eInt = ler(sEI);
  dInt = ler(sDI);
  dExt = ler(sDE);
}