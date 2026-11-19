#include "mapa.h"

#include <random>

#include "constantes_sdl.h"

using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {
int tile_de_pixel(int pixel) {
  int tile = pixel / TAMANIO_TILE;
  if (pixel < 0 && pixel % TAMANIO_TILE != 0) {
    tile--;
  }
  return tile;
}

const char *archivo_tileset(SectorTypeDto tipo) {
  if (tipo == SectorTypeDto::FARM) {
    return RUTA_TILESET_GRANJA;
  } else if (tipo == SectorTypeDto::CAVERN) {
    return RUTA_TILESET_CAVERNA;
  }
  return RUTA_TILESET_PUEBLO;
}
} // namespace

Mapa::Mapa(Renderer &renderer, SectorTypeDto tipo, int ancho, int alto,
           unsigned int semilla)
    : suelo(renderer, archivo_tileset(tipo)), muebles(renderer, RUTA_MUEBLES),
      piso_pueblo(renderer, RUTA_TILESET_PUEBLO),
      flores(renderer, RUTA_OFRENDAS_CENTRO_COMUNITARIO),
      casa(renderer, RUTA_TILESET_CABANA), borde(LETRA_BORDE),
      tipo(tipo), margen(0) {
  if (tipo == SectorTypeDto::FARM) {
    generar_granja(ancho, alto, semilla);
  } else if (tipo == SectorTypeDto::CAVERN) {
    generar_caverna(ancho, alto, semilla);
  } else if (tipo == SectorTypeDto::VILLAGE) {
    generar_pueblo(ancho, alto, semilla);
  } else if (tipo == SectorTypeDto::COMMUNITY_CENTER) {
    generar_centro(ancho, alto);
  } else if (tipo == SectorTypeDto::CABIN) {
    generar_cabana(ancho, alto);
  }
}

void Mapa::generar_granja(int ancho, int alto, unsigned int /*semilla*/) {
  margen = MAPA_MARGEN;
  int ancho_total = ancho + 2 * margen;
  int alto_total = alto + 2 * margen;
  pasto_afuera.assign(alto_total, std::string(ancho_total, LETRA_PASTO));

  filas.clear();
  for (int y = 0; y < alto; y++) {
    filas.push_back(pasto_afuera[margen + y].substr(margen, ancho));
  }
}

void Mapa::generar_caverna(int ancho, int alto, unsigned int semilla) {
  borde = LETRA_BORDE_CAVERNA;

  filas.assign(alto, std::string(ancho, LETRA_PISO_CAVERNA));

  std::mt19937 azar(semilla);
  std::uniform_int_distribution<int> dado(0, MAPA_DADO_DECORACION_MAXIMO);
  for (int y = 0; y < alto; ++y) {
    for (int x = 0; x < ancho; ++x) {
      int numero = dado(azar);
      if (numero == 0)
        filas[y][x] = LETRA_CAVERNA_DECORACION_1;
      if (numero == 1)
        filas[y][x] = LETRA_CAVERNA_DECORACION_2;
    }
  }

  filas[0] = std::string(ancho, LETRA_PARED);
}

void Mapa::generar_pueblo(int ancho, int alto, unsigned int semilla) {
  margen = MAPA_MARGEN;
  int ancho_total = ancho + 2 * margen;
  int alto_total = alto + 2 * margen;
  pasto_afuera.assign(alto_total, std::string(ancho_total, LETRA_PISO_PUEBLO));

  filas.assign(alto, std::string(ancho, LETRA_PISO_PUEBLO));

  std::mt19937 azar(semilla);
  std::uniform_int_distribution<int> dado(0, MAPA_DADO_DECORACION_MAXIMO);
  for (int y = 0; y < alto_total; ++y) {
    for (int x = 0; x < ancho_total; ++x) {
      if (dado(azar) == 0) {
        pasto_afuera[y][x] = LETRA_FLORES;
      }
    }
  }
}

void Mapa::generar_centro(int ancho, int alto) {
  borde = LETRA_VACIO;
  filas.assign(alto, std::string(ancho, LETRA_PISO_PUEBLO));
}

void Mapa::generar_cabana(int ancho, int alto) {
  borde = LETRA_VACIO;
  filas.assign(alto, std::string(ancho, LETRA_PISO_MADERA));
}

int Mapa::obtener_ancho() const {
  if (filas.empty()) {
    return 0;
  }
  return static_cast<int>(filas[0].size());
}

int Mapa::obtener_alto() const { return static_cast<int>(filas.size()); }

// bool Mapa::es_escalera(int x, int y) const {
//   return tile_en(x, y) == LETRA_PUERTA;
// }

void Mapa::actualizar(const std::vector<std::vector<TileDto>> &tiles) {
  int ancho = static_cast<int>(tiles.size());
  int alto = 0;
  if (ancho > 0) {
    alto = static_cast<int>(tiles[0].size());
  }

  std::vector<std::string> nueva(alto, std::string(ancho, LETRA_PASTO));

  // El servidor decide que hay en cada lugar
  for (int x = 0; x < ancho; ++x) {
    for (int y = 0; y < alto; ++y) {
      const TileDto &tile = tiles[x][y];

      char letra = tile_en(x, y);
      if (tile.type == TerrainTypeDto::DIRT) {
        letra = LETRA_TIERRA;
      }
      if (tile.type == TerrainTypeDto::WOOD) {
        letra = LETRA_PISO_MADERA;
      }
      if (tile.tilled) {
        letra = LETRA_ARADO;
      }
      if (tile.isDoor) {
        letra = LETRA_PUERTA;
      }
      if (!tile.transitable && tipo == SectorTypeDto::CAVERN) {
        letra = LETRA_PARED;
      }

      nueva[y][x] = letra;
    }
  }
  filas = nueva;
}

char Mapa::tile_en(int x, int y) const {
  if (x >= 0 && x < obtener_ancho() && y >= 0 && y < obtener_alto()) {
    return filas[y][x];
  }
  int afuera_x = x + margen;
  int afuera_y = y + margen;
  if (!pasto_afuera.empty() && afuera_x >= 0 && afuera_y >= 0 &&
      afuera_y < static_cast<int>(pasto_afuera.size()) &&
      afuera_x < static_cast<int>(pasto_afuera[0].size())) {
    return pasto_afuera[afuera_y][afuera_x];
  }
  return borde;
}

void Mapa::dibujar_completo(Renderer &renderer, int origen_x, int origen_y,
                            int lado) {
  for (int fila = 0; fila < obtener_alto(); fila++) {
    for (int columna = 0; columna < obtener_ancho(); columna++) {
      int x = origen_x + columna * lado;
      int y = origen_y + fila * lado;
      dibujar_tile(renderer, filas[fila][columna], x, y, lado);
    }
  }
}

void Mapa::dibujar_tile(Renderer &renderer, char tipo_tile, int x, int y,
                        int lado) {
  if (tipo_tile == LETRA_VACIO) {
    return;
  }
  int columna = SUELO_DEFECTO_COLUMNA;
  int fila = SUELO_DEFECTO_FILA;
  if (tipo_tile == LETRA_BORDE_CAVERNA) {
    columna = SUELO_BORDE_CAVERNA_COLUMNA;
    fila = SUELO_BORDE_CAVERNA_FILA;
  }
  if (tipo_tile == LETRA_BORDE) {
    columna = SUELO_BORDE_COLUMNA;
    fila = SUELO_BORDE_FILA;
  }
  if (tipo_tile == LETRA_TIERRA) {
    columna = SUELO_TIERRA_COLUMNA;
    fila = SUELO_TIERRA_FILA;
  }
  if (tipo_tile == LETRA_ARADO) {
    columna = SUELO_ARADO_COLUMNA;
    fila = SUELO_ARADO_FILA;
  }
  if (tipo_tile == LETRA_PISO_CAVERNA) {
    columna = SUELO_PISO_CAVERNA_COLUMNA;
    fila = SUELO_PISO_CAVERNA_FILA;
  }
  if (tipo_tile == LETRA_CAVERNA_DECORACION_1) {
    columna = SUELO_CAVERNA_DECORACION_1_COLUMNA;
    fila = SUELO_CAVERNA_DECORACION_1_FILA;
  }
  if (tipo_tile == LETRA_CAVERNA_DECORACION_2) {
    columna = SUELO_CAVERNA_DECORACION_2_COLUMNA;
    fila = SUELO_CAVERNA_DECORACION_2_FILA;
  }
  if (tipo_tile == LETRA_PARED) {
    columna = SUELO_PARED_COLUMNA;
    fila = SUELO_PARED_FILA;
  }
  if (tipo_tile == LETRA_PUERTA && tipo != SectorTypeDto::CAVERN) {
    int alto = SPRITE_PUERTA_ALTO * lado / SPRITE_PUERTA_ANCHO;
    Rect origen(SPRITE_PUERTA_X, SPRITE_PUERTA_Y, SPRITE_PUERTA_ANCHO,
                SPRITE_PUERTA_ALTO);
    renderer.Copy(muebles, origen, Rect(x, y + lado - alto, lado, alto));
    return;
  }

  Rect piso(SPRITE_PISO_PUEBLO_X, SPRITE_PISO_PUEBLO_Y, PIXELES_POR_TILE,
            PIXELES_POR_TILE);
  if (tipo_tile == LETRA_PISO_PUEBLO && tipo != SectorTypeDto::CAVERN) {
    renderer.Copy(piso_pueblo, piso, Rect(x, y, lado, lado));
    return;
  }

  if (tipo_tile == LETRA_FLORES) {
    Rect flor(SPRITE_FLORES_X, SPRITE_FLORES_Y, PIXELES_POR_TILE,
              PIXELES_POR_TILE);
    renderer.Copy(piso_pueblo, piso, Rect(x, y, lado, lado));
    renderer.Copy(flores, flor, Rect(x, y, lado, lado));
    return;
  }

  if (tipo_tile == LETRA_PISO_MADERA) {
    Rect madera(SPRITE_PISO_MADERA_X, SPRITE_PISO_MADERA_Y, PIXELES_POR_TILE, PIXELES_POR_TILE);
    renderer.Copy(casa, madera, Rect(x, y, lado, lado));
    return;
  }

  Rect origen(columna * PIXELES_POR_TILE, fila * PIXELES_POR_TILE,
              PIXELES_POR_TILE, PIXELES_POR_TILE);
  Rect destino(x, y, lado, lado);
  renderer.Copy(suelo, origen, destino);
}

void Mapa::dibujar(Renderer &renderer, int camara_x, int camara_y,
                   int ancho_ventana, int alto_ventana, bool incluir_margen) {
  int primera_columna = tile_de_pixel(camara_x);
  int primera_fila = tile_de_pixel(camara_y);
  int ultima_columna = tile_de_pixel(camara_x + ancho_ventana);
  int ultima_fila = tile_de_pixel(camara_y + alto_ventana);

  for (int fila = primera_fila; fila <= ultima_fila; ++fila) {
    for (int columna = primera_columna; columna <= ultima_columna; ++columna) {
      int x = columna * TAMANIO_TILE - camara_x;
      int y = fila * TAMANIO_TILE - camara_y;
      bool afuera = columna < 0 || fila < 0 || columna >= obtener_ancho() ||
                    fila >= obtener_alto();
      if (afuera && !incluir_margen) {
        continue;
      }
      if (afuera) {
        suelo.SetColorMod(COLOR_SOMBRA_MARGEN, COLOR_SOMBRA_MARGEN,
                          COLOR_SOMBRA_MARGEN);
      }
      dibujar_tile(renderer, tile_en(columna, fila), x, y, TAMANIO_TILE);
      if (afuera) {
        suelo.SetColorMod(COLOR_SIN_TINTE, COLOR_SIN_TINTE, COLOR_SIN_TINTE);
      }
    }
  }
}
