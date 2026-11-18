#ifndef ANIMACION_ENEMIGOS_H
#define ANIMACION_ENEMIGOS_H

#include <SDL2pp/SDL2pp.hh>

#include "animacion.h"

class AnimacionEnemigo {
public:
  enum class Estado {
    QUIETO,
    CAMINANDO,
    ATACANDO,
    GOLPEADO,
    MURIENDO,
    TIRADO,
    REVIVIENDO
  };

private:
  long vueltas_caminando = 0;
  long vueltas_atacando = 0;
  long vueltas_daniado = 0;
  long vueltas_muriendo = 0;
  long vueltas_reviviendo = 0;
  bool mira_izquierda = false;

  void mirar_hacia(int dx);

public:
  void caminar(int dx, long duracion);
  void atacar(int dx, long duracion);
  void recibir_golpe(long duracion);
  void morir(long duracion);
  void revivir(long duracion);

  void animar(long vueltas);

  bool esta_atacando() const;
  bool mira_a_la_izquierda() const;

  Estado estado(bool vivo) const;

  long restantes(Estado estado) const;
};

struct HojasEnemigo {
  const char *quieto;
  const char *caminando;
  const char *atacando;
  const char *daniado;
  const char *muerte;
  int lado;
  int pie;
  int pie_caminando;
  int centro_x;
};

class SpritesEnemigo {
private:
  Animacion quieto;
  Animacion caminando;
  Animacion atacando;
  Animacion daniado;
  Animacion muerte;

public:
  SpritesEnemigo(SDL2pp::Renderer &renderer, const HojasEnemigo &hojas);

  long duracion_ataque() const;
  long duracion_golpe() const;
  long duracion_muerte() const;

  void dibujar(SDL2pp::Renderer &renderer, const AnimacionEnemigo &animacion,
               bool vivo, long vueltas_totales, int tile_x, int tile_y,
               int camara_x, int camara_y, int lado_tile,
               const SDL2pp::Color &tinte);
};

#endif
