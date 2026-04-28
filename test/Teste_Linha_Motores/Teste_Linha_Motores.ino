#include "motores.h"
#include "sensoresLinha.h"
#include "../include/pinos.h"

#include "Arduino.h"

// ==========================================
// ENUM DE MOVIMENTO
// ==========================================
enum Movimento {
  FRENTE,
  CURVA_ESQUERDA,
  CURVA_DIREITA,
  VIRAR_ESQUERDA,
  VIRAR_DIREITA,
  PARADO
};

// ==========================================
// LÓGICA DOS 4 SENSORES
// ==========================================
Movimento calcularMovimento(bool eExt, bool eInt, bool dInt, bool dExt) {

  // Linha central (ideal)
  if (eInt && dInt) {
    return FRENTE;
  }

  // Muito para esquerda
  if ((eExt || eInt) && !dInt && !dExt) {
    if (eExt && eInt) return VIRAR_ESQUERDA;
    return CURVA_ESQUERDA;
  }

  // Muito para direita
  if ((dExt || dInt) && !eInt && !eExt) {
    if (dExt && dInt) return VIRAR_DIREITA;
    return CURVA_DIREITA;
  }

  // Correções leves
  if (eInt) return CURVA_ESQUERDA;
  if (dInt) return CURVA_DIREITA;

  // Perdeu a linha
  return PARADO;
}

// ==========================================
// EXECUÇÃO DO MOVIMENTO
// ==========================================
void executarMovimento(Movimento mov) {
  switch (mov) {
    case FRENTE:
      andarFrente();
      break;

    case CURVA_ESQUERDA:
      curvaEsquerda();
      break;

    case CURVA_DIREITA:
      curvaDireita();
      break;

    case VIRAR_ESQUERDA:
      virarEsquerda();
      break;

    case VIRAR_DIREITA:
      virarDireita();
      break;

    case PARADO:
    default:
      pararMotores();
      break;
  }
}

// ==========================================
// SETUP
// ==========================================
void setup() {
  motores_init(
    MOTOR_ESQ_AVANCA,
    MOTOR_ESQ_RECUA,
    MOTOR_DIR_AVANCA,
    MOTOR_DIR_RECUA
  );

  sensores_init(
    PINO_ESQ_EXT,
    PINO_ESQ_INT,
    PINO_DIR_INT,
    PINO_DIR_EXT
  );

  pararMotores();
  delay(1000);
}

// ==========================================
// LOOP
// ==========================================
void loop() {
  bool eExt, eInt, dInt, dExt;

  lerSensores(eExt, eInt, dInt, dExt);

  Movimento mov = calcularMovimento(eExt, eInt, dInt, dExt);

  executarMovimento(mov);

  delay(20);
}