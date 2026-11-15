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

  struct Mineral {
    TipoMineral tipo;
    int tile_x;
    int tile_y;
    size_t golpes;
  };

  SDL2pp::Texture minerales;
  std::vector<Mineral> lista_minerales;

  long vueltas;

  void dibujar_mineral(SDL2pp::Renderer &renderer, const Mineral &mineral,
                       int camara_x, int camara_y, int lado);

public:
  explicit Caverna(SDL2pp::Renderer &renderer);

  void actualizar(const std::map<GamePositionDto, EntityDto> &entidades);

  void animar(long vueltas_pasadas);

  void dibujar(SDL2pp::Renderer &renderer, int camara_x, int camara_y,
               int lado = 64);
};

#endif
