#include "alrededores.h"

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;

namespace {
const int ESCALA = 4;
const int TILE = 16 * ESCALA;

const int ZONA = 30;
const int SEPARACION = 3;
const int PORCENTAJE_BOSQUE = 50;
const int SOMBRA = 200;
const int MARGEN = 4;

int entre(std::mt19937 &azar, int minimo, int maximo) {
  std::uniform_int_distribution<int> dado(minimo, maximo);
  return dado(azar);
}
} // namespace

Alrededores::Alrededores(Renderer &renderer, int ancho_granja, int alto_granja,
                         unsigned int semilla)
    : arbol(renderer, "assets/mapas/tree1.png"),
      pino(renderer, "assets/mapas/tree1_2.png"), ancho_granja(ancho_granja),
      alto_granja(alto_granja) {

  // Texturas de afuera
  arbol.SetColorMod(SOMBRA, SOMBRA, SOMBRA);
  pino.SetColorMod(SOMBRA, SOMBRA, SOMBRA);

  std::mt19937 azar(semilla);

  for (int y = -ZONA; y < alto_granja + ZONA; y += SEPARACION) {
    for (int x = -ZONA; x < ancho_granja + ZONA; x += SEPARACION) {
      int arbol_x = x + entre(azar, 0, SEPARACION - 2);
      int arbol_y = y + entre(azar, 0, SEPARACION - 2);
      bool hay_arbol = entre(azar, 0, 99) < PORCENTAJE_BOSQUE;
      bool es_pino = entre(azar, 0, 1) == 0;
      if (hay_arbol && !cerca_de_la_granja(arbol_x, arbol_y)) {
        lista_arboles.push_back({es_pino, arbol_x, arbol_y});
      }
    }
  }
}

bool Alrededores::cerca_de_la_granja(int x, int y) const {
  bool cerca_en_x = x >= -1 && x <= ancho_granja;
  bool cerca_en_y = y >= -1 && y <= alto_granja;
  return cerca_en_x && cerca_en_y;
}

void Alrededores::dibujar_arbol(Renderer &renderer, const Arbol &un_arbol,
                                int camara_x, int camara_y) {
  Texture *textura = &arbol;
  if (un_arbol.es_pino) {
    textura = &pino;
  }

  int ancho = textura->GetWidth() * ESCALA;
  int alto = textura->GetHeight() * ESCALA;
  int x = un_arbol.tile_x * TILE + TILE / 2 - ancho / 2 - camara_x;
  int y = (un_arbol.tile_y + 1) * TILE - alto - camara_y;
  renderer.Copy(*textura, NullOpt, Rect(x, y, ancho, alto));
}

void Alrededores::dibujar(Renderer &renderer, int camara_x, int camara_y,
                          int ancho_ventana, int alto_ventana) {
  for (const Arbol &un_arbol : lista_arboles) {
    int x = un_arbol.tile_x * TILE - camara_x;
    int y = un_arbol.tile_y * TILE - camara_y;
    bool lejos = x < -MARGEN * TILE || x > ancho_ventana + MARGEN * TILE ||
                 y < -MARGEN * TILE || y > alto_ventana + MARGEN * TILE;
    if (lejos) {
      continue;
    }
    dibujar_arbol(renderer, un_arbol, camara_x, camara_y);
  }
}
