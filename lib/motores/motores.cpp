#include <Arduino.h>
#include "pinos.h"
#include "motores.h"

static uint8_t pinIN1 = PININ1;
static uint8_t pinIN2 = PININ2;
static uint8_t pinIN3 = PININ3;
static uint8_t pinIN4 = PININ4;
static uint8_t pinENA = PINENA;
static uint8_t pinENB = PINENB;

static uint8_t limitarPwm(int valor)
{
    if (valor < 0)
        return 0;
    if (valor > 255)
        return 255;
    return (uint8_t)valor;
}

static void pararMotor(uint8_t in1, uint8_t in2, uint8_t en)
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(en, 0);
}

static void motorFrente(uint8_t in1, uint8_t in2, uint8_t en, uint8_t velocidade)
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(en, limitarPwm(velocidade));
}

static void motorRe(uint8_t in1, uint8_t in2, uint8_t en, uint8_t velocidade)
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(en, limitarPwm(velocidade));
}

void motores_init()
{
    motores_init(PININ1, PININ2, PININ3, PININ4);
}

void motores_init(int pin1, int pin2, int pin3, int pin4)
{
    pinIN1 = pin1;
    pinIN2 = pin2;
    pinIN3 = pin3;
    pinIN4 = pin4;

    pinENA = PINENA;
    pinENB = PINENB;

    pinMode(pinIN1, OUTPUT);
    pinMode(pinIN2, OUTPUT);
    pinMode(pinIN3, OUTPUT);
    pinMode(pinIN4, OUTPUT);
    pinMode(pinENA, OUTPUT);
    pinMode(pinENB, OUTPUT);

    pararMotores();
}

void pararMotores()
{
    pararMotor(pinIN1, pinIN2, pinENA);
    pararMotor(pinIN3, pinIN4, pinENB);
}

void andarFrente(uint8_t velocidade)
{
    motorFrente(pinIN1, pinIN2, pinENA, velocidade);
    motorFrente(pinIN3, pinIN4, pinENB, velocidade);
}

void andarRe(uint8_t velocidade)
{
    motorRe(pinIN1, pinIN2, pinENA, velocidade);
    motorRe(pinIN3, pinIN4, pinENB, velocidade);
}

void curvaEsquerda(uint8_t velocidadeBase, uint8_t reducao)
{
    uint8_t velEsq = (velocidadeBase > reducao) ? (velocidadeBase - reducao) : 0;
    uint8_t velDir = velocidadeBase;

    motorFrente(pinIN1, pinIN2, pinENA, velEsq);
    motorFrente(pinIN3, pinIN4, pinENB, velDir);
}

void curvaDireita(uint8_t velocidadeBase, uint8_t reducao)
{
    uint8_t velDir = (velocidadeBase > reducao) ? (velocidadeBase - reducao) : 0;
    uint8_t velEsq = velocidadeBase;

    motorFrente(pinIN1, pinIN2, pinENA, velEsq);
    motorFrente(pinIN3, pinIN4, pinENB, velDir);
}

void virarEsquerda(uint8_t velocidade)
{
    motorRe(pinIN1, pinIN2, pinENA, velocidade);
    motorFrente(pinIN3, pinIN4, pinENB, velocidade);
}

void virarDireita(uint8_t velocidade)
{
    motorFrente(pinIN1, pinIN2, pinENA, velocidade);
    motorRe(pinIN3, pinIN4, pinENB, velocidade);
}

void testeMotoresSequencial()
{
    Serial.println(F("Teste: frente"));
    andarFrente(190);
    delay(1800);
    pararMotores();
    delay(500);

    Serial.println(F("Teste: curva esquerda"));
    curvaEsquerda(180, 80);
    delay(1500);
    pararMotores();
    delay(500);

    Serial.println(F("Teste: curva direita"));
    curvaDireita(180, 80);
    delay(1500);
    pararMotores();
    delay(500);

    Serial.println(F("Teste: giro esquerdo"));
    virarEsquerda(170);
    delay(1200);
    pararMotores();
    delay(500);

    Serial.println(F("Teste: giro direito"));
    virarDireita(170);
    delay(1200);
    pararMotores();
    delay(500);

    Serial.println(F("Teste: ré"));
    andarRe(170);
    delay(1500);
    pararMotores();
    delay(500);

    Serial.println(F("Teste finalizado"));
}