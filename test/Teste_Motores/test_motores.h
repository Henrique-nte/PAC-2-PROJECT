#ifndef MOTORES_H
#define MOTORES_H

#include <Arduino.h>

// Inicialização padrão usando os pinos definidos em pinos.h
void motores_init();

// Inicialização alternativa, caso queira reaproveitar o módulo com outro mapeamento
void motores_init(int pinIN1, int pinIN2, int pinIN3, int pinIN4);

// Controles principais
void pararMotores();
void andarFrente(uint8_t velocidade = 180);
void andarRe(uint8_t velocidade = 180);

// Curvas suaves
void curvaEsquerda(uint8_t velocidadeBase = 170, uint8_t reducao = 70);
void curvaDireita(uint8_t velocidadeBase = 170, uint8_t reducao = 70);

// Giro no lugar
void virarEsquerda(uint8_t velocidade = 170);
void virarDireita(uint8_t velocidade = 170);

// Sequência automática de teste
void testeMotoresSequencial();

#endif