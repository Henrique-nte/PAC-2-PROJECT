#ifndef PINOS_H
#define PINOS_H

/*
 * MAPA DE CONFIGURAÇÃO DE PINOS - Robô Seguidor de Linha com Garra
 * 
 * Abreviações:
 *  eExt/eInt = Esquerda Externa/Interna
 *  dExt/dInt = Direita Externa/Interna
 *  Avanca/Recua = Marcha frente/ré
 * 
 */

// ===== SENSORES DE LINHA =====
#define PINO_ESQ_EXT 2     // Pino digital - Sensor linha ESQUERDA externa
#define PINO_ESQ_INT 3     // Pino digital - Sensor linha ESQUERDA interna
#define PINO_DIR_INT 11    // Pino digital - Sensor linha DIREITA interna
#define PINO_DIR_EXT 12    // Pino digital - Sensor linha DIREITA externa

// ===== SENSOR ULTRASSÔNICO =====
#define PINO_TRIG 8        // Pino digital - Trigger para enviar pulso
#define PINO_ECHO 9        // Pino digital - Lê tempo de retorno

// ===== MOTORES =====
// Motor Esquerdo
#define MOTOR_ESQ_AVANCA 4    // Pino digital - Avanço motor esquerdo
#define MOTOR_ESQ_RECUA 5     // Pino digital - Ré motor esquerdo

// Motor Direito
#define MOTOR_DIR_AVANCA 6    // Pino digital - Avanço motor direito
#define MOTOR_DIR_RECUA 7     // Pino digital - Ré motor direito


// ===== SERVO/GARRA =====
#define PINO_SERVO 10      // Pino PWM (3,5,6,9,10,11) - Controle servo

#endif