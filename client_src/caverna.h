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
  enum TipoEnemigo { ESQUELETO, ORCO, VAMPIRO, VAMPIRA };

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
  };

  SDL2pp::Texture minerales;
  SDL2pp::Texture esqueleto;
  SDL2pp::Texture orco_quieto;
  SDL2pp::Texture orco_caminando;
  SDL2pp::Texture orco_atacando;
  SDL2pp::Texture vampiro_quieto;
  SDL2pp::Texture vampiro_caminando;
  SDL2pp::Texture vampiro_atacando;
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

  void dibujar_mineral(SDL2pp::Renderer &renderer, const Mineral &mineral,
                       int camara_x, int camara_y, int lado);
  void dibujar_enemigo(SDL2pp::Renderer &renderer, const Enemigo &enemigo,
                       int camara_x, int camara_y, int lado);

public:
  explicit Caverna(SDL2pp::Renderer &renderer);

  void actualizar(const std::map<GamePositionDto, EntityDto> &entidades);

  // Un jugador en ese tile perdió vida: los orcos de al lado le pegaron
  void golpearon_a(int tile_x, int tile_y);

  void animar(long vueltas_pasadas);

  void dibujar(SDL2pp::Renderer &renderer, int camara_x, int camara_y,
               int lado = 64);
};

#endif
