#ifndef MAPA_MUNDO_H
#define MAPA_MUNDO_H

#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/game_dtos.h"
#include "caverna.h"
#include "granja.h"
#include "mapa.h"
#include "personaje.h"
#include "pueblo.h"

// Tecla M muestra todos los sectores a la vez
class MapaMundo {
private:
    struct Region {
        SectorTypeDto tipo;
        int x;
        int y;
        int ancho;
        int alto;
        Mapa *mapa;
    };

    int ancho;
    int alto;
    std::vector<Region> regiones;

    Granja &granja;
    Pueblo &pueblo;
    Caverna &caverna;

    int lado;
    int origen_x;
    int origen_y;

    void ubicar_sectores(const WorldMapDto &mapa_mundo, Mapa &mapa_granja, Mapa &mapa_puebl, Mapa &mapa_caverna);
    const Region *buscar_region(SectorTypeDto tipo) const;
    void difuminar_bordes(SDL2pp::Renderer &renderer, int x, int y, int ancho_px, int alto_px);
public:
    MapaMundo(const WorldMapDto &mapa_mundo, Mapa &mapa_granja, Mapa &mapa_puebl, Mapa &mapa_caverna, Granja &granja, Pueblo &pueblo, Caverna &caverna);

    void dibujar(SDL2pp::Renderer &renderer, int ancho_ventana, int alto_ventana, SectorTypeDto zona, Personaje &yo);
};

#endif
