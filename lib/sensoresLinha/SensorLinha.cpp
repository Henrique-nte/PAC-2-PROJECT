#include "SensorLinha.h"

SensorLinha::SensorLinha(bool linhaPreta)
    : _threshold(TRESHOLD), _linhaPreta(linhaPreta)
{
    _pinos[0] = S1;
    _pinos[1] = S2;
    _pinos[2] = S3;
    _pinos[3] = S4;
    _pinos[4] = S5;
    _pinos[5] = S6;

    memset(&_leitura, 0, sizeof(_leitura));
    _leitura.posicao = 2500;
    _leitura.erro = 0;
    _leitura.estado = CENTRO;
}

void SensorLinha::begin(uint16_t threshold)
{
    _threshold = threshold;
    for (uint8_t i = 0; i < NUM_SENSORES; i++)
    {
        pinMode(_pinos[i], INPUT);
    }
    ler();
}

void SensorLinha::setThreshold(uint16_t threshold)
{
    _threshold = threshold;
}

void SensorLinha::setLinhaPreta(bool linhaPreta)
{
    _linhaPreta = linhaPreta;
}

void SensorLinha::calibrate(uint16_t duracaoMs)
{
    uint16_t minimo[NUM_SENSORES];
    uint16_t maximo[NUM_SENSORES];

    for (uint8_t i = 0; i < NUM_SENSORES; i++)
    {
        minimo[i] = 1023;
        maximo[i] = 0;
    }

    unsigned long inicio = millis();
    while (millis() - inicio < duracaoMs)
    {
        for (uint8_t i = 0; i < NUM_SENSORES; i++)
        {
            uint16_t valor = analogRead(_pinos[i]);
            if (valor < minimo[i])
                minimo[i] = valor;
            if (valor > maximo[i])
                maximo[i] = valor;
        }
        delay(5);
    }

    uint32_t soma = 0;
    uint8_t ativos = 0;
    for (uint8_t i = 0; i < NUM_SENSORES; i++)
    {
        if (maximo[i] > minimo[i])
        {
            soma += (uint32_t)minimo[i] + (uint32_t)maximo[i];
            ativos++;
        }
    }

    if (ativos > 0)
    {
        _threshold = soma / (ativos * 2);
    }

    ler();
}

void SensorLinha::ler()
{
    for (uint8_t i = 0; i < NUM_SENSORES; i++)
    {
        _leitura.bruto[i] = analogRead(_pinos[i]);

        bool detectou = _linhaPreta ? (_leitura.bruto[i] < _threshold)
                                    : (_leitura.bruto[i] > _threshold);
        _leitura.digital[i] = detectou ? 1 : 0;
    }

    _leitura.mascara = calcularMascara();
    _leitura.posicao = calcularPosicao();
    _leitura.erro = _leitura.posicao - 2500;
    _leitura.estado = classificarEstado();
}

const SensorLinha::Leitura &SensorLinha::getLeitura() const
{
    return _leitura;
}

uint16_t SensorLinha::getValor(uint8_t indice) const
{
    if (indice >= NUM_SENSORES)
        return 0;
    return _leitura.bruto[indice];
}

uint8_t SensorLinha::getDigital(uint8_t indice) const
{
    if (indice >= NUM_SENSORES)
        return 0;
    return _leitura.digital[indice];
}

uint8_t SensorLinha::getMascara() const
{
    return _leitura.mascara;
}

int16_t SensorLinha::getPosicao() const
{
    return _leitura.posicao;
}

int16_t SensorLinha::getErro() const
{
    return _leitura.erro;
}

SensorLinha::EstadoLinha SensorLinha::getEstado() const
{
    return _leitura.estado;
}

bool SensorLinha::linhaPerdida() const
{
    return _leitura.mascara == 0;
}

bool SensorLinha::cruzamento() const
{
    return __builtin_popcount((unsigned int)_leitura.mascara) >= 5;
}

const char *SensorLinha::getEstadoTexto() const
{
    switch (_leitura.estado)
    {
    case ESQUERDA_FORTE:
        return "ESQUERDA_FORTE";
    case ESQUERDA:
        return "ESQUERDA";
    case CENTRO_ESQUERDA:
        return "CENTRO_ESQUERDA";
    case CENTRO:
        return "CENTRO";
    case CENTRO_DIREITA:
        return "CENTRO_DIREITA";
    case DIREITA:
        return "DIREITA";
    case DIREITA_FORTE:
        return "DIREITA_FORTE";
    case CRUZAMENTO:
        return "CRUZAMENTO";
    case LINHA_PERDIDA:
        return "LINHA_PERDIDA";
    default:
        return "DESCONHECIDO";
    }
}

void SensorLinha::calcularCorrecao(int baseVelocidade, int &velocidadeEsquerda, int &velocidadeDireita, int ajusteMaximo) const
{
    int erro = _leitura.erro; // -2500 a 2500
    int ajuste = map(erro, -2500, 2500, -ajusteMaximo, ajusteMaximo);

    velocidadeEsquerda = baseVelocidade - ajuste;
    velocidadeDireita = baseVelocidade + ajuste;

    velocidadeEsquerda = constrain(velocidadeEsquerda, 0, 255);
    velocidadeDireita = constrain(velocidadeDireita, 0, 255);

    if (linhaPerdida())
    {
        if (_leitura.erro < 0)
        {
            velocidadeEsquerda = 0;
            velocidadeDireita = constrain(baseVelocidade / 2, 0, 255);
        }
        else if (_leitura.erro > 0)
        {
            velocidadeEsquerda = constrain(baseVelocidade / 2, 0, 255);
            velocidadeDireita = 0;
        }
    }
}

void SensorLinha::imprimir(Stream &serial) const
{
    serial.print(F("Bruto: "));
    for (uint8_t i = 0; i < NUM_SENSORES; i++)
    {
        serial.print(_leitura.bruto[i]);
        if (i < NUM_SENSORES - 1)
            serial.print(F(" "));
    }

    serial.print(F(" | Digital: "));
    for (uint8_t i = 0; i < NUM_SENSORES; i++)
    {
        serial.print(_leitura.digital[i]);
        if (i < NUM_SENSORES - 1)
            serial.print(F(" "));
    }

    serial.print(F(" | Mascara: 0b"));
    for (int8_t i = NUM_SENSORES - 1; i >= 0; i--)
    {
        serial.print((_leitura.mascara >> i) & 0x01);
    }

    serial.print(F(" | Posicao: "));
    serial.print(_leitura.posicao);

    serial.print(F(" | Erro: "));
    serial.print(_leitura.erro);

    serial.print(F(" | Estado: "));
    serial.print(getEstadoTexto());

    serial.print(F(" | Threshold: "));
    serial.println(_threshold);
}

uint8_t SensorLinha::calcularMascara() const
{
    uint8_t mascara = 0;
    for (uint8_t i = 0; i < NUM_SENSORES; i++)
    {
        if (_leitura.digital[i])
        {
            mascara |= (1 << (NUM_SENSORES - 1 - i));
        }
    }
    return mascara;
}

int16_t SensorLinha::calcularPosicao() const
{
    static const int16_t pesos[NUM_SENSORES] = {0, 1000, 2000, 3000, 4000, 5000};

    uint32_t somaPesos = 0;
    uint32_t somaAtivos = 0;

    for (uint8_t i = 0; i < NUM_SENSORES; i++)
    {
        if (_leitura.digital[i])
        {
            somaPesos += (uint32_t)pesos[i];
            somaAtivos++;
        }
    }

    if (somaAtivos == 0)
    {
        return _leitura.posicao; // mantém a última posição conhecida
    }

    return (int16_t)(somaPesos / somaAtivos);
}

SensorLinha::EstadoLinha SensorLinha::classificarEstado() const
{
    if (_leitura.mascara == 0)
    {
        return LINHA_PERDIDA;
    }

    if (cruzamento())
    {
        return CRUZAMENTO;
    }

    switch (_leitura.mascara)
    {
    case 0b100000:
        return ESQUERDA_FORTE;
    case 0b110000:
    case 0b010000:
        return ESQUERDA;
    case 0b011000:
    case 0b001000:
        return CENTRO_ESQUERDA;
    case 0b001100:
    case 0b000100:
        return CENTRO;
    case 0b000110:
    case 0b000010:
        return CENTRO_DIREITA;
    case 0b000011:
    case 0b000001:
        return DIREITA;
    default:
        if (_leitura.posicao <= 800)
            return ESQUERDA_FORTE;
        if (_leitura.posicao <= 1800)
            return ESQUERDA;
        if (_leitura.posicao <= 2300)
            return CENTRO_ESQUERDA;
        if (_leitura.posicao <= 2700)
            return CENTRO;
        if (_leitura.posicao <= 3200)
            return CENTRO_DIREITA;
        if (_leitura.posicao <= 4200)
            return DIREITA;
        return DIREITA_FORTE;
    }
}