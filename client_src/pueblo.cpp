#include "pueblo.h"

#include <SDL2/SDL.h>

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {
const int ESCALA = 4;
const int TILE = 16 * ESCALA;

const SDL_Rect MODELOS_PUESTOS[4] = {
    {240, 176, 112, 144},   // Pierre's
    {80, 320, 144, 128},    // Clint
    {192, 640, 192, 160},   // Robin
    {256, 0, 144, 176},     // Marnie
};
}

Pueblo::Pueblo(Renderer &renderer)
    : edificios(renderer, "assets/edificios/PelicanTown_Buildings.png"),
      vueltas(0) {

    lista_puestos.push_back({10, 20, 0});
    lista_puestos.push_back({30, 36, 1});
    lista_puestos.push_back({29, 3, 2});
    lista_puestos.push_back({52, 18, 3});
}

void Pueblo::animar(long vueltas_pasadas) { vueltas += vueltas_pasadas; }

void Pueblo::dibujar_puesto(SDL2pp::Renderer &renderer, const Puesto &puesto, int camara_x, int camara_y, int lado) {
    const SDL_Rect &modelo = MODELOS_PUESTOS[puesto.modelo];
    Rect origen(modelo.x, modelo.y, modelo.w, modelo.h);

    int x = puesto.tile_x * lado - camara_x;
    int y = puesto.tile_y * lado - camara_y;
    Rect destino(x, y, modelo.w * lado / 16, modelo.h * lado / 16);
    renderer.Copy(edificios, origen, destino);
}

void Pueblo::dibujar(Renderer &renderer, int camara_x, int camara_y, int lado) {
  for (const Puesto &puesto : lista_puestos) {
    dibujar_puesto(renderer, puesto, camara_x, camara_y, lado);
  }
}

void Pueblo::actualizar(const std::map<GamePositionDto, EntityDto> &) {
  // hasta que mande el servidor
}