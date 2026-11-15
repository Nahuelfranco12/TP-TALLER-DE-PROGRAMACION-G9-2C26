#include "alrededores.h"

#include "constantes_sdl.h"

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;

namespace {
int entre(std::mt19937 &azar, int minimo, int maximo) {
  std::uniform_int_distribution<int> dado(minimo, maximo);
  return dado(azar);
}
}  // namespace

Alrededores::Alrededores(Renderer &renderer, int ancho_granja, int alto_granja,
                         unsigned int semilla)
    : arbol(renderer, RUTA_ARBOL), pino(renderer, RUTA_PINO),
      ancho_granja(ancho_granja), alto_granja(alto_granja) {

  // Texturas de afuera
  arbol.SetColorMod(BOSQUE_SOMBRA, BOSQUE_SOMBRA, BOSQUE_SOMBRA);
  pino.SetColorMod(BOSQUE_SOMBRA, BOSQUE_SOMBRA, BOSQUE_SOMBRA);

  std::mt19937 azar(semilla);

  for (int y = -BOSQUE_ZONA; y < alto_granja + BOSQUE_ZONA;
       y += BOSQUE_SEPARACION) {
    for (int x = -BOSQUE_ZONA; x < ancho_granja + BOSQUE_ZONA;
         x += BOSQUE_SEPARACION) {
      int arbol_x = x + entre(azar, 0, BOSQUE_DESPLAZAMIENTO_MAXIMO);
      int arbol_y = y + entre(azar, 0, BOSQUE_DESPLAZAMIENTO_MAXIMO);
      bool hay_arbol = entre(azar, 0, BOSQUE_DADO_MAXIMO) < BOSQUE_PORCENTAJE;
      bool es_pino = entre(azar, 0, 1) == 0;
      if (hay_arbol && !cerca_de_la_granja(arbol_x, arbol_y)) {
        lista_arboles.push_back({es_pino, arbol_x, arbol_y});
      }
    }
  }
}

bool Alrededores::cerca_de_la_granja(int x, int y) const {
  bool cerca_en_x = x >= -BOSQUE_DISTANCIA_GRANJA &&
                    x < ancho_granja + BOSQUE_DISTANCIA_GRANJA;
  bool cerca_en_y = y >= -BOSQUE_DISTANCIA_GRANJA &&
                    y < alto_granja + BOSQUE_DISTANCIA_GRANJA;
  return cerca_en_x && cerca_en_y;
}

void Alrededores::dibujar_arbol(Renderer &renderer, const Arbol &un_arbol,
                                int camara_x, int camara_y) {
  Texture *textura = &arbol;
  if (un_arbol.es_pino) {
    textura = &pino;
  }

  int ancho = textura->GetWidth() * ESCALA_SPRITES;
  int alto = textura->GetHeight() * ESCALA_SPRITES;
  int x = un_arbol.tile_x * TAMANIO_TILE + TAMANIO_TILE / 2 - ancho / 2 -
          camara_x;
  int y = (un_arbol.tile_y + 1) * TAMANIO_TILE - alto - camara_y;
  renderer.Copy(*textura, NullOpt, Rect(x, y, ancho, alto));
}

void Alrededores::dibujar(Renderer &renderer, int camara_x, int camara_y,
                          int ancho_ventana, int alto_ventana) {
  for (const Arbol &un_arbol : lista_arboles) {
    int x = un_arbol.tile_x * TAMANIO_TILE - camara_x;
    int y = un_arbol.tile_y * TAMANIO_TILE - camara_y;
    int margen = BOSQUE_MARGEN * TAMANIO_TILE;
    bool lejos = x < -margen || x > ancho_ventana + margen || y < -margen ||
                 y > alto_ventana + margen;
    if (lejos) {
      continue;
    }
    dibujar_arbol(renderer, un_arbol, camara_x, camara_y);
  }
}
