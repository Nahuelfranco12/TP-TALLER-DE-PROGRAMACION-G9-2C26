#ifndef CAVERNA_H
#define CAVERNA_H

#include <vector>
#include <map>

#include "../common_src/game_dtos.h"

#include <SDL2pp/SDL2pp.hh>

class Caverna {
private:
  enum TipoMineral { HIERRO, CARBON, LAPISLAZULI, ORO };

  struct Mineral {
    TipoMineral tipo;
    int tile_x;
    int tile_y;
    int golpes;
  };

  SDL2pp::Texture minerales;
  std::vector<Mineral> lista_minerales;

  long vueltas;

  void dibujar_mineral(SDL2pp::Renderer &renderer, const Mineral &mineral, int camara_x, int camara_y, int lado);

public:
  explicit Caverna(SDL2pp::Renderer &renderer);

  int picar(int tile_x, int tile_y);

  void animar(long vueltas_pasadas);

  void dibujar(SDL2pp::Renderer &renderer, int camara_x, int camara_y, int lado = 64);

  void actualizar(const std::map<GamePositionDto, EntityDto> &entidades);
};

#endif
