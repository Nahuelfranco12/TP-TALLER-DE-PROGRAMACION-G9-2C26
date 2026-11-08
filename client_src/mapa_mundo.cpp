#include "mapa_mundo.h"

#include <algorithm>

MapaMundo::MapaMundo(Mapa& granja, Mapa& pueblo, Mapa& caverna, int lado_tile) 
    : granja(granja),
      pueblo(pueblo),
      caverna(caverna),
      lado_tile(lado_tile) {}

void MapaMundo::dibujar(SDL2pp::Renderer& renderer, int camara_x, int camara_y, int ancho_ventana, int alto_ventana) {
    int origen_granja_x = 0;

    int origen_pueblo_x = granja.obtener_ancho() * lado_tile;

    int origen_caverna_x = origen_pueblo_x + pueblo.obtener_ancho() * lado_tile;

    granja.dibujar(renderer, camara_x - origen_granja_x, camara_y, ancho_ventana, alto_ventana, false);

    pueblo.dibujar(renderer, camara_x - origen_pueblo_x, camara_y, ancho_ventana, alto_ventana, false);

    caverna.dibujar(renderer, camara_x - origen_caverna_x, camara_y, ancho_ventana, alto_ventana, false);
}

int MapaMundo::obtener_ancho() const {
    return granja.obtener_ancho() + pueblo.obtener_ancho() + caverna.obtener_ancho();
}

int MapaMundo::obtener_alto() const {
    return std::max({granja.obtener_alto(), pueblo.obtener_alto(), caverna.obtener_alto()});
}