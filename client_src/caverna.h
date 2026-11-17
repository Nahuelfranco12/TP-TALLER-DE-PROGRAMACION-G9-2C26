#ifndef CAVERNA_H
#define CAVERNA_H

#include <map>
#include <vector>

#include "../common_src/game_dtos.h"
#include "animacion_enemigos.h"
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
    AnimacionEnemigo animacion;
    DirectionDto direction = DirectionDto::Up;
  };

  SDL2pp::Texture minerales;
  SpritesEnemigo sprites_esqueleto;
  SpritesEnemigo sprites_orco;
  SpritesEnemigo sprites_vampiro;
  SDL2pp::Texture calavera_azul_quieto;
  SDL2pp::Texture calavera_verde_quieto;
  SDL2pp::Texture pinches;
  SDL2pp::Texture lanzallamas_1;
  SDL2pp::Texture lanzallamas_2;
  std::vector<Mineral> lista_minerales;
  std::vector<Enemigo> lista_enemigos;

  long vueltas;

  static bool hay_enemigo(const std::vector<Enemigo> &lista, TipoEnemigo tipo,
                          int x, int y);

  void seguir_movimiento(Enemigo &enemigo,
                         const std::vector<Enemigo> &anteriores,
                         const std::vector<Enemigo> &actuales);

  SpritesEnemigo *sprites_de(TipoEnemigo tipo);

  void dibujar_mineral(SDL2pp::Renderer &renderer, const Mineral &mineral,
                       int camara_x, int camara_y, int lado);
  void dibujar_enemigo(SDL2pp::Renderer &renderer, const Enemigo &enemigo,
                       int camara_x, int camara_y, int lado);

public:
  explicit Caverna(SDL2pp::Renderer &renderer);

  void actualizar(const std::map<GamePositionDto, EntityDto> &entidades);

  void golpear(int tile_x, int tile_y);

  void golpearon_a(int tile_x, int tile_y);

  void animar(long vueltas_pasadas);

  void dibujar(SDL2pp::Renderer &renderer, int camara_x, int camara_y,
               int lado = 64);
};

#endif
