#ifndef GARRA_H
#define GARRA_H

#include <Servo.h>

// Estados da garra conforme máquina de estados
enum EstadoGarra {
  GARRA_ABERTA,       // Posição inicial (0°) - seguro
  GARRA_FECHANDO,     // Servo movendo 0° → 90°
  GARRA_FECHADA,      // Objeto capturado (90°)
  GARRA_ROTACIONANDO, // Robô executando giro 90° de descarte
  GARRA_ABRINDO       // Servo movendo 90° → 0°
};

class Garra {
public:
  // Inicializa servo no pino indicado e posiciona em ABERTA
  void begin(int pino);

  // Inicia fechamento para capturar objeto (só aceita se ABERTA)
  void fechar();

  // Inicia abertura para soltar objeto (só aceita se FECHADA ou ROTACIONANDO)
  void abrir();

  // Transição FECHADA → ROTACIONANDO (robô vai girar 90° para depositar)
  void iniciarDeposito();

  // Transição ROTACIONANDO → ABRINDO (giro concluído, abre garra)
  void finalizarDeposito();

  // Chame a cada ciclo do loop - gerencia watchdog e transições de tempo
  void update();

  EstadoGarra getEstado() const;
  bool estaAberta()       const;
  bool estaFechada()      const;
  bool estaRotacionando() const;

private:
  Servo _servo;
  int _pino;
  EstadoGarra _estado;
  unsigned long _tempoComando;

  static const int ANGULO_ABERTA  = 0;   // graus
  static const int ANGULO_FECHADA = 90;  // graus - ajuste conforme testes físicos

  // Tempo estimado para o servo completar o movimento (ms)
  static const unsigned long TEMPO_MOVIMENTO = 600;

  // Watchdog fixo (não escala com velocidade_global) - conforme requisito
  static const unsigned long TIMEOUT_SERVO = 3000;

  void _resetarServoPorFalha();
};

#endif
