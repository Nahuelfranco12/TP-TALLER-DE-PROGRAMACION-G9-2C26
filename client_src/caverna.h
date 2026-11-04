#ifndef CAVERNA_H
#define CAVERNA_H

#include <vector>

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

public:
  explicit Caverna(SDL2pp::Renderer &renderer);

  bool picar(int tile_x, int tile_y);

  void dibujar(SDL2pp::Renderer &renderer, int camara_x, int camara_y,
               int lado = 64);
};

#endif
