#ifndef SENSORES_LINHA_H
#define SENSORES_LINHA_H

/**
 * MÓDULO DE SENSORES DE LINHA
 * =============================
 * 
 * Implementa lógica de 4 sensores IR reflexivos (2 esquerda, 2 direita)
 * 
 * Convenção de Lógica:
 *   LOW (0V)  = Sensor detecta linha (superfície preta) - RETORNA TRUE
 *   HIGH (5V) = Sensor vê ar/branco - RETORNA FALSE
 * 
 * Uso:
 *   1. Chamar sensores_init() uma vez em setup()
 *   2. Chamar lerSensores() a cada loop para atualizar bool's
 */

void sensores_init(int eExt, int eInt, int dInt, int dExt);

/**
 * Lê estado de todos os 4 sensores
 * @param eExt Referência: true=linha detectada (esq externa)
 * @param eInt Referência: true=linha detectada (esq interna)
 * @param dInt Referência: true=linha detectada (dir interna)
 * @param dExt Referência: true=linha detectada (dir externa)
 */
void lerSensores(bool &eExt, bool &eInt, bool &dInt, bool &dExt);

#endif