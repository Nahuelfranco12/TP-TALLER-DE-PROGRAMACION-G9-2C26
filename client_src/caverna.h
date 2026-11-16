#ifndef CAVERNA_H
#define CAVERNA_H

#include <map>
#include <vector>

#include "../common_src/game_dtos.h"
#include "constantes_sdl.h"

#include <SDL2pp/SDL2pp.hh>

class Caverna {
private:
  enum TipoMineral { HIERRO, CARBON, LAPISLAZULI, ORO };
  enum TipoEnemigo {
    ESQUELETO,
    ORCO,
    VAMPIRO,
    VAMPIRA,
    CALAVERA_AZUL,
    CALAVERA_VERDE,
    TRAMPA_PINCHES,
    TRAMPA_LANZALLAMAS
  };

  struct Mineral {
    TipoMineral tipo;
    int tile_x;
    int tile_y;
    size_t golpes;
  };

  struct Enemigo {
    TipoEnemigo tipo;
    int tile_x;
    int tile_y;
    bool vivo;
    long vueltas_caminando;
    long vueltas_atacando;
    bool mira_izquierda;
    DirectionDto direction = DirectionDto::Up;
  };

  SDL2pp::Texture minerales;
  SDL2pp::Texture esqueleto;
  SDL2pp::Texture esqueleto_caminando;
  SDL2pp::Texture esqueleto_atacando;
  SDL2pp::Texture orco_quieto;
  SDL2pp::Texture orco_caminando;
  SDL2pp::Texture orco_atacando;
  SDL2pp::Texture vampiro_quieto;
  SDL2pp::Texture vampiro_caminando;
  SDL2pp::Texture vampiro_atacando;
  SDL2pp::Texture calavera_azul_quieto;
  SDL2pp::Texture calavera_verde_quieto;
  SDL2pp::Texture pinches;
  SDL2pp::Texture lanzallamas_1;
  SDL2pp::Texture lanzallamas_2;
  std::vector<Mineral> lista_minerales;
  std::vector<Enemigo> lista_enemigos;

  long vueltas;

  // Si en la lista hay un enemigo de ese tipo en ese tile
  static bool hay_enemigo(const std::vector<Enemigo> &lista, TipoEnemigo tipo,
                          int x, int y);

  // Busca al enemigo en el estado anterior para saber si se movió
  static void seguir_movimiento(Enemigo &enemigo,
                                const std::vector<Enemigo> &anteriores,
                                const std::vector<Enemigo> &actuales);

  // Cuántas vueltas dura una pasada de la hoja de ataque de ese tipo
  long duracion_ataque(TipoEnemigo tipo) const;

  void dibujar_mineral(SDL2pp::Renderer &renderer, const Mineral &mineral,
                       int camara_x, int camara_y, int lado);
  void dibujar_enemigo(SDL2pp::Renderer &renderer, const Enemigo &enemigo,
                       int camara_x, int camara_y, int lado);

public:
  explicit Caverna(SDL2pp::Renderer &renderer);

  void actualizar(const std::map<GamePositionDto, EntityDto> &entidades);

  void golpearon_a(int tile_x, int tile_y);

  void animar(long vueltas_pasadas);

  void dibujar(SDL2pp::Renderer &renderer, int camara_x, int camara_y,
               int lado = 64);
};

#endif
