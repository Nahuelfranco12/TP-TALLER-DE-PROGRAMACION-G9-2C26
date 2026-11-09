#include "mapa_mundo.h"

#include <algorithm>

#include <SDL.h>

using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {
    const int MARGEN = 8;
    const int SEPARACION = 14;
    const int PASILLO = 10;
    const int BAJADA_PUEBLO = 24;
    const int MARGEN_PANTALLA = 16;
    const SDL2pp::Color COLOR_FONDO = {54, 124, 66, 25};
    const int TILES_DIFUMINADO = 3;
}

MapaMundo::MapaMundo(const WorldMapDto &mapa_mundo, Mapa &mapa_granja, Mapa &mapa_pueblo, Mapa &mapa_caverna, Granja &granja, Pueblo &pueblo, Caverna &caverna)
    : ancho(0), alto(0), granja(granja), pueblo(pueblo), caverna(caverna), lado(1), origen_x(0), origen_y(0) {
        ubicar_sectores(mapa_mundo, mapa_granja, mapa_pueblo, mapa_caverna);
}

// Dónde va cada sector dentro del mapa grande
void MapaMundo::ubicar_sectores(const WorldMapDto &mapa_mundo, Mapa &mapa_granja, Mapa &mapa_pueblo, Mapa &mapa_caverna) {
    int pueblo_x = MARGEN + PASILLO;
    int granja_x = pueblo_x + mapa_pueblo.obtener_ancho() + SEPARACION;
    int caverna_x = granja_x;
    int caverna_y = MARGEN;
    int granja_y = caverna_y + mapa_caverna.obtener_alto() + SEPARACION;
    int pueblo_y = granja_y + BAJADA_PUEBLO;

    for (const SectorStateDto &sector : mapa_mundo.sectors) {
        if (sector.type == SectorTypeDto::FARM) {
            regiones.push_back({sector.type, granja_x, granja_y, mapa_granja.obtener_ancho(), mapa_granja.obtener_alto(), &mapa_granja});
        } else if (sector.type == SectorTypeDto::VILLAGE) {
            regiones.push_back({sector.type, pueblo_x, pueblo_y, mapa_pueblo.obtener_ancho(), mapa_pueblo.obtener_alto(), &mapa_pueblo});
        } else {
            regiones.push_back({sector.type, caverna_x, caverna_y, mapa_caverna.obtener_ancho(), mapa_caverna.obtener_alto(), &mapa_caverna});
        }
    }

    ancho = granja_x + std::max(mapa_granja.obtener_ancho(), mapa_caverna.obtener_ancho()) + MARGEN;
    alto = std::max(granja_y + mapa_granja.obtener_alto(), pueblo_y + mapa_pueblo.obtener_alto()) + MARGEN;
}

const MapaMundo::Region *MapaMundo::buscar_region(SectorTypeDto tipo) const {
    for (const Region &region : regiones) {
        if (region.tipo == tipo) {
            return &region;
        }
    }
    return nullptr;
}

void MapaMundo::dibujar(Renderer &renderer, int ancho_ventana, int alto_ventana, SectorTypeDto zona, Personaje &yo) {
    // Tamaño de cada tile para que entre todo
    int lado_ancho = (ancho_ventana - 2 * MARGEN_PANTALLA) / ancho;
    int lado_alto = (alto_ventana - 2 * MARGEN_PANTALLA) / alto;
    lado = std::max(1, std::min(lado_ancho, lado_alto));
    origen_x = (ancho_ventana - ancho * lado) / 2;
    origen_y = (alto_ventana - alto * lado) / 2;

    // Fondo
    renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
    renderer.SetDrawColor(18, 22, 18, 255);
    renderer.Clear();
    renderer.SetDrawColor(COLOR_FONDO.r, COLOR_FONDO.g, COLOR_FONDO.b, 255);
    renderer.FillRect(Rect(origen_x, origen_y, ancho * lado, alto * lado));

    // Cada sector tiene su suelo, sus cosas
    for (const Region &region : regiones) {
        int x = origen_x + region.x * lado;
        int y = origen_y + region.y * lado;

        region.mapa->dibujar_completo(renderer, x, y, lado);
        if (region.tipo == SectorTypeDto::FARM) {
            granja.dibujar(renderer, -x, -y, lado);
        } else if (region.tipo == SectorTypeDto::VILLAGE) {
            pueblo.dibujar(renderer, -x, -y, lado);
        } else {
            caverna.dibujar(renderer, -x, -y, lado);
        }

        difuminar_bordes(renderer, x, y, region.ancho * lado, region.alto * lado);
    }

    const Region *actual = buscar_region(zona);
    if (actual != nullptr) {
        int lado_figura = std::max(12, 4 * lado);
        int centro_x = origen_x + (actual->x + yo.obtener_tile_x()) * lado + lado / 2;
        int pie_y = origen_y + (actual->y + yo.obtener_tile_y() + 1) * lado;
        yo.dibujar_icono(renderer, centro_x, pie_y, lado_figura);
    }
}

void MapaMundo::difuminar_bordes(Renderer &renderer, int x, int y, int ancho_px, int alto_px) {
    int ancho_difuminado = TILES_DIFUMINADO * lado;
    for (int i = 0; i < ancho_difuminado; i++) {
        int alfa = 255 * (ancho_difuminado - i) / ancho_difuminado;
        renderer.SetDrawColor(COLOR_FONDO.r, COLOR_FONDO.g, COLOR_FONDO.b, static_cast<Uint8>(alfa));

        renderer.FillRect(Rect(x + i, y + i, ancho_px - 2 * i, 1)); //arriba
        renderer.FillRect(Rect(x + i, y + alto_px - 1 - i, ancho_px -2 * i, 1)); //abajo
        renderer.FillRect(Rect(x + i, y + i + 1, 1, alto_px - 2 * i - 2)); //izquierda
        renderer.FillRect(Rect(x + ancho_px - 1 - i, y + i + 1, 1, alto_px - 2 * i - 2)); //derecha
    }
}