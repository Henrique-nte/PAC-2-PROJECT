#include "SensorLinha.h"

SensorLinha sensores(true);

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        ;
    }

    sensores.begin(TRESHOLD);

    Serial.println(F("=== TESTE SENSOR DE LINHA ==="));
    Serial.println(F("Comandos:"));
    Serial.println(F("  c -> recalibrar por 3 segundos"));
    Serial.println(F("  p -> imprimir leitura imediata"));
    Serial.println();
}

void loop()
{
    if (Serial.available() > 0)
    {
        char comando = Serial.read();

        if (comando == 'c' || comando == 'C')
        {
            Serial.println(F("Calibrando... mova o robô sobre a linha e o fundo."));
            sensores.calibrate(3000);
            Serial.println(F("Calibracao concluida."));
        }

        if (comando == 'p' || comando == 'P')
        {
            sensores.ler();
            sensores.imprimir(Serial);
        }
    }

    sensores.ler();
    sensores.imprimir(Serial);

    int velEsq = 0;
    int velDir = 0;
    sensores.calcularCorrecao(150, velEsq, velDir, 90);

    Serial.print(F("Ajuste sugerido -> ESQ: "));
    Serial.print(velEsq);
    Serial.print(F(" DIR: "));
    Serial.println(velDir);

    Serial.println(F("----------------------------------------------"));
    delay(200);
}