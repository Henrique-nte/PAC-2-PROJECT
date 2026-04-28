#include <Arduino.h>
#include "garra.h"

void Garra::begin(int pino) {
  _pino = pino;
  _servo.attach(pino);
  _servo.write(ANGULO_ABERTA);
  _estado = GARRA_ABERTA;
  _tempoComando = 0;
}

void Garra::fechar() {
  if (_estado != GARRA_ABERTA) return;
  _servo.write(ANGULO_FECHADA);
  _estado = GARRA_FECHANDO;
  _tempoComando = millis();
}

void Garra::abrir() {
  if (_estado != GARRA_FECHADA && _estado != GARRA_ROTACIONANDO) return;
  _servo.write(ANGULO_ABERTA);
  _estado = GARRA_ABRINDO;
  _tempoComando = millis();
}

void Garra::iniciarDeposito() {
  if (_estado != GARRA_FECHADA) return;
  _estado = GARRA_ROTACIONANDO;
}

void Garra::finalizarDeposito() {
  if (_estado != GARRA_ROTACIONANDO) return;
  abrir();
}

void Garra::update() {
  unsigned long decorrido = millis() - _tempoComando;

  if (_estado == GARRA_FECHANDO) {
    if (decorrido >= TIMEOUT_SERVO) {
      // Watchdog: servo travado ou com falha - força estado seguro
      _resetarServoPorFalha();
    } else if (decorrido >= TEMPO_MOVIMENTO) {
      // Movimento concluído normalmente
      _estado = GARRA_FECHADA;
    }
  }
  else if (_estado == GARRA_ABRINDO) {
    if (decorrido >= TIMEOUT_SERVO) {
      _resetarServoPorFalha();
    } else if (decorrido >= TEMPO_MOVIMENTO) {
      _estado = GARRA_ABERTA;
    }
  }
}

EstadoGarra Garra::getEstado() const {
  return _estado;
}

bool Garra::estaAberta() const {
  return _estado == GARRA_ABERTA;
}

bool Garra::estaFechada() const {
  return _estado == GARRA_FECHADA;
}

bool Garra::estaRotacionando() const {
  return _estado == GARRA_ROTACIONANDO;
}

// --- Privado ---

void Garra::_resetarServoPorFalha() {
  // Libera e reanexa o servo para destravar sinal PWM preso
  _servo.detach();
  _servo.attach(_pino);
  _servo.write(ANGULO_ABERTA);
  _estado = GARRA_ABERTA;
}
