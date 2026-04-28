#ifndef MOTORES_H
#define MOTORES_H

/**
 * MÓDULO DE MOTORES
 * ==================
 * 
 * Controla 2 motores DC via módulo L298N
 * 
 * LÓGICA:
 *   Motor = Par de pinos (Avança, Recua)
 *   HIGH em Avança + LOW em Recua = Motor gira frente
 *   LOW em Avança + HIGH em Recua = Motor gira ré
 *   LOW em ambos = Motor parado
 * 
 * IMPORTANTE - FAIL-SAFE:
 *   NUNCA colocar HIGH em Avança E Recua simultaneamente!
 *   (Causaria curto no L298N)
 *   Todas as funções reseta ambos pinos antes de set novo estado.
 */

void motores_init(int eA, int eR, int dA, int dR);

// ===== MOVIMENTOS SIMPLES =====
void andarFrente();   // Ambos motores avançam
void andarRe();       // Ambos motores recuam
void pararMotores();  // Reseta todos os pinos

// ===== CURVAS SUAVES (raio maior) =====
void curvaEsquerda();   // Motor direito avança, esquerdo parado
void curvaDireita();    // Motor esquerdo avança, direito parado

// ===== ROTAÇÕES AGUDAS (raio menor) =====
void virarEsquerda();   // Motor direito frente, esquerdo ré
void virarDireita();    // Motor esquerdo frente, direito ré

#endif