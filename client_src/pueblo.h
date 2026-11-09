#ifndef PUEBLO_H
#define PUEBLO_H

#include <vector>
#include <map>

#include "../common_src/game_dtos.h"

#include <SDL2pp/SDL2pp.hh>

class Pueblo {
private:
    struct Puesto {
        int tile_x;
        int tile_y;
        int modelo;
    };

    SDL2pp::Texture edificios;

    std::vector<Puesto> lista_puestos;

    long vueltas;

    void dibujar_puesto(SDL2pp::Renderer &renderer, const Puesto &puesto, int camara_x, int camara_y, int lado);

public:
    explicit Pueblo(SDL2pp::Renderer &renderer);
    
    void animar(long vueltas_pasadas);
    
    void dibujar(SDL2pp::Renderer &renderer, int camara_x, int camara_y, int lado = 64);
    
    void actualizar(const std::map<GamePositionDto, EntityDto> &entidades);
};

#endif
