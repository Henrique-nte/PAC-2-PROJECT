#ifndef SENSOR_LINHA_H
#define SENSOR_LINHA_H

#include <Arduino.h>
#include "pinos.h"

class SensorLinha
{
public:
    static const uint8_t NUM_SENSORES = 6;

    enum EstadoLinha : uint8_t
    {
        ESQUERDA_FORTE = 0,
        ESQUERDA,
        CENTRO_ESQUERDA,
        CENTRO,
        CENTRO_DIREITA,
        DIREITA,
        DIREITA_FORTE,
        CRUZAMENTO,
        LINHA_PERDIDA
    };

    struct Leitura
    {
        uint16_t bruto[NUM_SENSORES];
        uint8_t digital[NUM_SENSORES];
        uint8_t mascara;
        int16_t posicao; // 0 a 5000
        int16_t erro;    // posicao - 2500
        EstadoLinha estado;
    };

    explicit SensorLinha(bool linhaPreta = true);

    void begin(uint16_t threshold = TRESHOLD);
    void setThreshold(uint16_t threshold);
    void setLinhaPreta(bool linhaPreta);

    void calibrate(uint16_t duracaoMs = 3000);
    void ler();

    const Leitura &getLeitura() const;
    uint16_t getValor(uint8_t indice) const;
    uint8_t getDigital(uint8_t indice) const;
    uint8_t getMascara() const;
    int16_t getPosicao() const;
    int16_t getErro() const;
    EstadoLinha getEstado() const;

    bool linhaPerdida() const;
    bool cruzamento() const;

    const char *getEstadoTexto() const;

    void calcularCorrecao(int baseVelocidade, int &velocidadeEsquerda, int &velocidadeDireita, int ajusteMaximo = 120) const;
    void imprimir(Stream &serial) const;

private:
    uint8_t _pinos[NUM_SENSORES];
    uint16_t _threshold;
    bool _linhaPreta;
    Leitura _leitura;

    int16_t calcularPosicao() const;
    EstadoLinha classificarEstado() const;
    uint8_t calcularMascara() const;
};

#endif