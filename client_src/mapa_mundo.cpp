#include "mapa_mundo.h"

#include <algorithm>
#include <random>

#include <SDL.h>

#include "constantes_sdl.h"

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;

MapaMundo::MapaMundo(Renderer &renderer, const WorldMapDto &mapa_mundo,
                     Mapa &mapa_granja, Mapa &mapa_pueblo, Mapa &mapa_caverna,
                     Granja &granja, Pueblo &pueblo, Caverna &caverna)
    : ancho(0), alto(0), granja(granja), pueblo(pueblo), caverna(caverna),
      suelo(renderer, RUTA_TILESET_GRANJA), arbol(renderer, RUTA_ARBOL),
      pino(renderer, RUTA_PINO), lado(1), origen_x(0), origen_y(0) {
  ubicar_sectores(mapa_mundo, mapa_granja, mapa_pueblo, mapa_caverna);
  plantar_arboles();
}

// Dónde va cada sector dentro del mapa grande
void MapaMundo::ubicar_sectores(const WorldMapDto &mapa_mundo,
                                Mapa &mapa_granja, Mapa &mapa_pueblo,
                                Mapa &mapa_caverna) {
  int pueblo_x = MUNDO_MARGEN + MUNDO_PASILLO;
  int granja_x = pueblo_x + mapa_pueblo.obtener_ancho() + MUNDO_SEPARACION;
  int caverna_x = granja_x;
  int caverna_y = MUNDO_MARGEN;
  int granja_y = caverna_y + mapa_caverna.obtener_alto() + MUNDO_SEPARACION;
  int pueblo_y = granja_y + MUNDO_BAJADA_PUEBLO;

  for (const SectorStateDto &sector : mapa_mundo.sectors) {
    if (sector.type == SectorTypeDto::FARM) {
      regiones.push_back({sector.type, granja_x, granja_y,
                          mapa_granja.obtener_ancho(),
                          mapa_granja.obtener_alto(), &mapa_granja});
    } else if (sector.type == SectorTypeDto::VILLAGE) {
      regiones.push_back({sector.type, pueblo_x, pueblo_y,
                          mapa_pueblo.obtener_ancho(),
                          mapa_pueblo.obtener_alto(), &mapa_pueblo});
    } else {
      regiones.push_back({sector.type, caverna_x, caverna_y,
                          mapa_caverna.obtener_ancho(),
                          mapa_caverna.obtener_alto(), &mapa_caverna});
    }
  }

  ancho = granja_x +
          std::max(mapa_granja.obtener_ancho(), mapa_caverna.obtener_ancho()) +
          MUNDO_MARGEN;
  alto = std::max(granja_y + mapa_granja.obtener_alto(),
                  pueblo_y + mapa_pueblo.obtener_alto()) +
         MUNDO_MARGEN;
}

bool MapaMundo::es_bosque(int x, int y) const {
  for (const Region &region : regiones) {
    bool adentro = x >= region.x && x < region.x + region.ancho &&
                   y >= region.y && y < region.y + region.alto;
    if (adentro) {
      return false;
    }
  }
  return true;
}

void MapaMundo::plantar_arboles() {
  std::mt19937 azar(MUNDO_SEMILLA);
  std::uniform_int_distribution<int> corrimiento(0, MUNDO_ENTRE_ARBOLES - 1);
  std::uniform_int_distribution<int> dado(0, MUNDO_DADO_MAXIMO);

  for (int y = 0; y < alto; y += MUNDO_ENTRE_ARBOLES) {
    for (int x = 0; x < ancho; x += MUNDO_ENTRE_ARBOLES) {
      int ax = x + corrimiento(azar);
      int ay = y + corrimiento(azar);
      bool hay = dado(azar) < MUNDO_PROBABILIDAD_ARBOL;
      bool es_pino = dado(azar) < MUNDO_PROBABILIDAD_PINO;
      if (hay && es_bosque(ax, ay)) {
        arboles.push_back({ax, ay, es_pino});
      }
    }
  }
  std::sort(arboles.begin(), arboles.end(),
            [](const Arbol &a, const Arbol &b) { return a.y < b.y; });
}

const MapaMundo::Region *MapaMundo::buscar_region(SectorTypeDto tipo) const {
  for (const Region &region : regiones) {
    if (region.tipo == tipo) {
      return &region;
    }
  }
  return nullptr;
}

void MapaMundo::dibujar(Renderer &renderer, int ancho_ventana, int alto_ventana,
                        SectorTypeDto zona, Personaje &yo) {
  // Tamaño de cada tile para que entre todo
  int lado_ancho = (ancho_ventana - 2 * MUNDO_MARGEN_PANTALLA) / ancho;
  int lado_alto = (alto_ventana - 2 * MUNDO_MARGEN_PANTALLA) / alto;
  lado = std::max(1, std::min(lado_ancho, lado_alto));
  origen_x = (ancho_ventana - ancho * lado) / 2;
  origen_y = (alto_ventana - alto * lado) / 2;

  // Fondo
  const SDL2pp::Color fondo = COLOR_MUNDO_FONDO;
  renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
  renderer.SetDrawColor(fondo);
  renderer.Clear();

  dibujar_bosque(renderer);

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

  dibujar_arboles(renderer);

  const Region *actual = buscar_region(zona);
  if (actual != nullptr) {
    int lado_figura = std::max(MUNDO_FIGURA_MINIMA, MUNDO_FIGURA_TILES * lado);
    int centro_x =
        origen_x + (actual->x + yo.obtener_tile_x()) * lado + lado / 2;
    int pie_y = origen_y + (actual->y + yo.obtener_tile_y() + 1) * lado;
    yo.dibujar_icono(renderer, centro_x, pie_y, lado_figura);
  }
}

void MapaMundo::dibujar_bosque(Renderer &renderer) {
  Rect pasto_oscuro(SPRITE_PASTO_OSCURO_X, SPRITE_PASTO_OSCURO_Y,
                    TAMANIO_TILE_ASSET, TAMANIO_TILE_ASSET);
  for (int y = 0; y < alto; y += MUNDO_BLOQUE_PASTO) {
    for (int x = 0; x < ancho; x += MUNDO_BLOQUE_PASTO) {
      int bloque_ancho = std::min(MUNDO_BLOQUE_PASTO, ancho - x);
      int bloque_alto = std::min(MUNDO_BLOQUE_PASTO, alto - y);
      Rect destino(origen_x + x * lado, origen_y + y * lado,
                   bloque_ancho * lado, bloque_alto * lado);
      renderer.Copy(suelo, pasto_oscuro, destino);
    }
  }
}

void MapaMundo::dibujar_arboles(Renderer &renderer) {
  for (const Arbol &un_arbol : arboles) {
    SDL2pp::Texture *textura = &arbol;
    if (un_arbol.es_pino) {
      textura = &pino;
    }
    int arbol_ancho = MUNDO_ARBOL_TILES * lado;
    int arbol_alto = arbol_ancho * textura->GetHeight() / textura->GetWidth();

    int x = origen_x + un_arbol.x * lado + lado / 2 - arbol_ancho / 2;
    int y = origen_y + (un_arbol.y + 1) * lado - arbol_alto;
    renderer.Copy(*textura, NullOpt, Rect(x, y, arbol_ancho, arbol_alto));
  }
}

void MapaMundo::difuminar_bordes(Renderer &renderer, int x, int y, int ancho_px,
                                 int alto_px) {
  const SDL2pp::Color fondo = COLOR_MUNDO_DIFUMINADO;
  int ancho_difuminado = MUNDO_TILES_DIFUMINADO * lado;
  for (int i = 0; i < ancho_difuminado; i++) {
    int alfa = COLOR_ALFA_OPACO * (ancho_difuminado - i) / ancho_difuminado;
    renderer.SetDrawColor(fondo.r, fondo.g, fondo.b, static_cast<Uint8>(alfa));

    renderer.FillRect(Rect(x + i, y + i, ancho_px - 2 * i, 1)); // arriba
    renderer.FillRect(
        Rect(x + i, y + alto_px - 1 - i, ancho_px - 2 * i, 1)); // abajo
    renderer.FillRect(
        Rect(x + i, y + i + 1, 1, alto_px - 2 * i - 2)); // izquierda
    renderer.FillRect(Rect(x + ancho_px - 1 - i, y + i + 1, 1,
                           alto_px - 2 * i - 2)); // derecha
  }
}
