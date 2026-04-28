#ifndef PINOS_H
#define PINOS_H

// ===== MOTORES (Configuração Original) =====
#define PININ1 2
#define PININ2 4
#define PININ3 5
#define PININ4 7
#define PINENA 3 // PWM - Velocidade Motor A
#define PINENB 6 // PWM - Velocidade Motor B

// ===== SENSORES DE LINHA QTR (Configuração Original) =====
#define S1 A0
#define S2 A1
#define S3 A2
#define S4 A3
#define S5 A4
#define S6 A5

// ===== SENSOR ULTRASSÔNICO (Adaptado) =====
#define PINO_TRIG 8
#define PINO_ECHO 9

// ===== SERVO / GARRA (Adaptado) =====
#define PINO_SERVO 10 // Pino PWM para controle da Garra

// ===== LED RGB (Remanejado para evitar conflitos) =====
#define PINLEDR 11
#define PINLEDG 12
#define PINLEDB 13

// =====================================================
// VALORES DE AJUSTE E LÓGICA (MIF)
// =====================================================
#define TRESHOLD 700
#define RUNTIME 15500

// Perfis de Velocidade (PWM 0-255)
#define SPEED0 255 // (0 0 1 1 0 0)
#define SPEED1 220 // (0 0 1 1 1 0)
#define SPEED2 150 // (0 0 0 1 0 0)
#define SPEED3 100 // (0 0 0 1 1 0)
#define SPEED4 80  // (0 0 0 1 1 1)
#define SPEED5 50  // (0 0 0 0 1 0)
#define SPEED6 0   // (0 0 0 0 1 1)
#define SPEED7 200 // (0 0 0 0 0 1)

#endif