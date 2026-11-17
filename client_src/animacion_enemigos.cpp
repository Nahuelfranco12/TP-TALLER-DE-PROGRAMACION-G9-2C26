#include "animacion_enemigos.h"

#include "constantes_sdl.h"

using SDL2pp::Renderer;

namespace {
void descontar(long &contador, long vueltas) {
  if (contador > 0) {
    contador -= vueltas;
  }
}
} // namespace

void AnimacionEnemigo::mirar_hacia(int dx) {
  if (dx < 0) {
    mira_izquierda = true;
  } else if (dx > 0) {
    mira_izquierda = false;
  }
}

void AnimacionEnemigo::caminar(int dx, long duracion) {
  vueltas_caminando = duracion;
  mirar_hacia(dx);
}

void AnimacionEnemigo::atacar(int dx, long duracion) {
  vueltas_atacando = duracion;
  mirar_hacia(dx);
}

void AnimacionEnemigo::recibir_golpe(long duracion) {
  vueltas_daniado = duracion;
}

void AnimacionEnemigo::morir(long duracion) {
  vueltas_muriendo = duracion;
  vueltas_reviviendo = 0;
  vueltas_daniado = 0;
  vueltas_atacando = 0;
  vueltas_caminando = 0;
}

void AnimacionEnemigo::revivir(long duracion) {
  vueltas_reviviendo = duracion;
  vueltas_muriendo = 0;
}

void AnimacionEnemigo::animar(long vueltas) {
  descontar(vueltas_caminando, vueltas);
  descontar(vueltas_atacando, vueltas);
  descontar(vueltas_daniado, vueltas);
  descontar(vueltas_muriendo, vueltas);
  descontar(vueltas_reviviendo, vueltas);
}

bool AnimacionEnemigo::esta_atacando() const { return vueltas_atacando > 0; }

bool AnimacionEnemigo::mira_a_la_izquierda() const { return mira_izquierda; }

AnimacionEnemigo::Estado AnimacionEnemigo::estado(bool vivo) const {
  if (!vivo) {
    if (vueltas_muriendo > 0) {
      return Estado::MURIENDO;
    }
    return Estado::TIRADO;
  }
  if (vueltas_reviviendo > 0) {
    return Estado::REVIVIENDO;
  }
  if (vueltas_daniado > 0) {
    return Estado::GOLPEADO;
  }
  if (vueltas_atacando > 0) {
    return Estado::ATACANDO;
  }
  if (vueltas_caminando > 0) {
    return Estado::CAMINANDO;
  }
  return Estado::QUIETO;
}

long AnimacionEnemigo::restantes(Estado actual) const {
  switch (actual) {
  case Estado::CAMINANDO:
    return vueltas_caminando;
  case Estado::ATACANDO:
    return vueltas_atacando;
  case Estado::GOLPEADO:
    return vueltas_daniado;
  case Estado::MURIENDO:
    return vueltas_muriendo;
  case Estado::REVIVIENDO:
    return vueltas_reviviendo;
  case Estado::QUIETO:
  case Estado::TIRADO:
    break;
  }
  return 0;
}

// SpritesEnemigo

SpritesEnemigo::SpritesEnemigo(Renderer &renderer, const HojasEnemigo &hojas)
    : quieto(renderer, hojas.quieto, hojas.lado, hojas.pie, hojas.centro_x,
             VUELTAS_POR_CUADRO_ENEMIGO),
      caminando(renderer, hojas.caminando, hojas.lado, hojas.pie_caminando,
                hojas.centro_x, VUELTAS_POR_CUADRO_ENEMIGO),
      atacando(renderer, hojas.atacando, hojas.lado, hojas.pie,
               hojas.centro_x, VUELTAS_POR_CUADRO_ENEMIGO),
      daniado(renderer, hojas.daniado, hojas.lado, hojas.pie, hojas.centro_x,
              VUELTAS_POR_CUADRO_ENEMIGO),
      muerte(renderer, hojas.muerte, hojas.lado, hojas.pie, hojas.centro_x,
             VUELTAS_POR_CUADRO_ENEMIGO) {}

long SpritesEnemigo::duracion_ataque() const { return atacando.duracion(); }

long SpritesEnemigo::duracion_golpe() const { return daniado.duracion(); }

long SpritesEnemigo::duracion_muerte() const { return muerte.duracion(); }

void SpritesEnemigo::dibujar(Renderer &renderer,
                             const AnimacionEnemigo &animacion, bool vivo,
                             long vueltas_totales, int tile_x, int tile_y,
                             int camara_x, int camara_y, int lado_tile,
                             const SDL2pp::Color &tinte) {
  AnimacionEnemigo::Estado estado = animacion.estado(vivo);
  long restantes = animacion.restantes(estado);

  Animacion *hoja = &quieto;
  int cuadro = 0;
  switch (estado) {
  case AnimacionEnemigo::Estado::QUIETO:
    cuadro = quieto.cuadro_en_bucle(vueltas_totales);
    break;
  case AnimacionEnemigo::Estado::CAMINANDO:
    hoja = &caminando;
    cuadro = caminando.cuadro_en_bucle(vueltas_totales);
    break;
  case AnimacionEnemigo::Estado::ATACANDO:
    hoja = &atacando;
    cuadro = atacando.cuadro_de_pasada(restantes);
    break;
  case AnimacionEnemigo::Estado::GOLPEADO:
    hoja = &daniado;
    cuadro = daniado.cuadro_de_pasada(restantes);
    break;
  case AnimacionEnemigo::Estado::MURIENDO:
    hoja = &muerte;
    cuadro = muerte.cuadro_de_pasada(restantes);
    break;
  case AnimacionEnemigo::Estado::TIRADO:
    hoja = &muerte;
    cuadro = muerte.ultimo_cuadro();
    break;
  case AnimacionEnemigo::Estado::REVIVIENDO:
    hoja = &muerte;
    cuadro = muerte.cuadro_al_reves(restantes);
    break;
  }

  hoja->dibujar(renderer, cuadro, tile_x, tile_y, camara_x, camara_y,
                lado_tile, animacion.mira_a_la_izquierda(), tinte);
}
