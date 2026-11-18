#include "animacion.h"

#include <algorithm>

#include "constantes_sdl.h"

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;

Animacion::Animacion(Renderer &renderer, const std::string &ruta, int lado,
                     int pie, int centro_x, long vueltas)
    : textura(renderer, ruta), lado_cuadro(lado), fila_pie(pie),
      columna_centro(centro_x), vueltas_por_cuadro(vueltas) {}

int Animacion::cuadros() const { return textura.GetWidth() / lado_cuadro; }

long Animacion::duracion() const {
  return static_cast<long>(cuadros()) * vueltas_por_cuadro;
}

int Animacion::limitar(long cuadro) const {
  int ultimo = std::max(cuadros() - 1, 0);
  return std::clamp(static_cast<int>(cuadro), 0, ultimo);
}

int Animacion::cuadro_en_bucle(long vueltas_totales) const {
  int total = cuadros();
  if (total <= 0) {
    return 0;
  }
  return static_cast<int>((vueltas_totales / vueltas_por_cuadro) % total);
}

int Animacion::cuadro_de_pasada(long vueltas_restantes) const {
  return limitar((duracion() - vueltas_restantes) / vueltas_por_cuadro);
}

int Animacion::cuadro_al_reves(long vueltas_restantes) const {
  return limitar(vueltas_restantes / vueltas_por_cuadro);
}

int Animacion::ultimo_cuadro() const { return limitar(cuadros() - 1); }

void Animacion::dibujar(Renderer &renderer, int cuadro, int tile_x, int tile_y,
                        int camara_x, int camara_y, int lado_tile,
                        bool espejada, const SDL2pp::Color &tinte) {
  if (cuadros() <= 0) {
    return;
  }

  int tamanio = lado_cuadro * lado_tile / PIXELES_POR_TILE;
  int x = tile_x * lado_tile + lado_tile / 2 - tamanio / 2 - camara_x;
  int y = tile_y * lado_tile + lado_tile -
          fila_pie * lado_tile / PIXELES_POR_TILE - camara_y;

  int flip = SDL_FLIP_NONE;
  if (espejada) {
    flip = SDL_FLIP_HORIZONTAL;
    x += (2 * columna_centro - lado_cuadro) * lado_tile / PIXELES_POR_TILE;
  }

  Rect origen(cuadro * lado_cuadro, 0, lado_cuadro, lado_cuadro);
  textura.SetColorMod(tinte.r, tinte.g, tinte.b);
  renderer.Copy(textura, origen, Rect(x, y, tamanio, tamanio), 0.0, NullOpt,
                flip);
  textura.SetColorMod(COLOR_SIN_TINTE, COLOR_SIN_TINTE, COLOR_SIN_TINTE);
}
