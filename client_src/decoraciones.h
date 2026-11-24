#ifndef DECORACIONES_H
#define DECORACIONES_H

#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/game_dtos.h"
#include "constantes_sdl.h"

struct Decoracion {
    int tile_x;
    int tile_y;
    TerrainDecorationDto tipo;
};

class Decoraciones {
private:
    std::vector<SDL2pp::Texture> imagenes;
public:
    explicit Decoraciones(SDL2pp::Renderer &renderer);

    void dibujar(SDL2pp::Renderer &renderer, const std::vector<Decoracion> &decoraciones, int camara_x, int camara_y, int lado = TAMANIO_TILE);
};

#endif
