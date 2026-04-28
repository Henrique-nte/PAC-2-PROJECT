#include <Arduino.h>
#include "pinos.h"
#include "motores.h"

static void mostrarAjuda()
{
    Serial.println(F("Comandos via Serial:"));
    Serial.println(F("  f = frente"));
    Serial.println(F("  r = re"));
    Serial.println(F("  e = curva esquerda"));
    Serial.println(F("  d = curva direita"));
    Serial.println(F("  q = giro esquerdo"));
    Serial.println(F("  w = giro direito"));
    Serial.println(F("  p = parar"));
    Serial.println(F("  t = teste sequencial"));
    Serial.println();
}

void setup()
{
    Serial.begin(9600);

    pinMode(PINLEDR, OUTPUT);
    pinMode(PINLEDG, OUTPUT);
    pinMode(PINLEDB, OUTPUT);

    digitalWrite(PINLEDR, LOW);
    digitalWrite(PINLEDG, LOW);
    digitalWrite(PINLEDB, LOW);

    motores_init();
    pararMotores();

    Serial.println(F("=== TESTE NOVO DE MOTORES ==="));
    Serial.println(F("Inicializando..."));
    delay(1000);

    mostrarAjuda();

    Serial.println(F("Executando sequencia automatica"));
    testeMotoresSequencial();
    Serial.println(F("Agora em modo manual"));
}

void loop()
{
    if (!Serial.available())
        return;

    char comando = Serial.read();

    switch (comando)
    {
    case 'f':
    case 'F':
        Serial.println(F("Frente"));
        andarFrente(190);
        break;

    case 'r':
    case 'R':
        Serial.println(F("Re"));
        andarRe(170);
        break;

    case 'e':
    case 'E':
        Serial.println(F("Curva esquerda"));
        curvaEsquerda(180, 80);
        break;

    case 'd':
    case 'D':
        Serial.println(F("Curva direita"));
        curvaDireita(180, 80);
        break;

    case 'q':
    case 'Q':
        Serial.println(F("Giro esquerdo"));
        virarEsquerda(170);
        break;

    case 'w':
    case 'W':
        Serial.println(F("Giro direito"));
        virarDireita(170);
        break;

    case 'p':
    case 'P':
        Serial.println(F("Parar"));
        pararMotores();
        break;

    case 't':
    case 'T':
        Serial.println(F("Rodando teste sequencial"));
        testeMotoresSequencial();
        break;

    case '\n':
    case '\r':
        break;

    default:
        Serial.println(F("Comando invalido"));
        mostrarAjuda();
        break;
    }
}