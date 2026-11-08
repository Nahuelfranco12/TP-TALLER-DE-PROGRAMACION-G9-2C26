#ifndef MAPA_MUNDO_H
#define MAPA_MUNDO_H

#include <SDL2pp/SDL2pp.hh>

#include "mapa.h"

class MapaMundo {
private:
    Mapa& granja;
    Mapa& pueblo;
    Mapa& caverna;

    int lado_tile;
public:
    MapaMundo(Mapa& granja, Mapa& pueblo, Mapa& caverna, int lado_tyle);

    void dibujar(SDL2pp::Renderer& renderer, int camara_x, int camara_y, int ancho_ventana, int alto_ventana);

    int obtener_ancho() const;
    int obtener_alto() const;
};

#endif
