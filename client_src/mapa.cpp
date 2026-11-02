#include "mapa.h"

#include <random>

using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {
const int ESCALA = 4;
const int TILE_SHEET = 16;
const int TILE = TILE_SHEET * ESCALA;

const char BORDE = ',';

int tile_de_pixel(int pixel) {
  int tile = pixel / TILE;
  if (pixel < 0 && pixel % TILE != 0) {
    tile--;
  }
  return tile;
}

const char* archivo_tileset(SectorTypeDto tipo) {
    if (tipo == SectorTypeDto::FARM) {
        return "assets/mapas/ground_01_16x16.png";
    }
    return "assets/mapas/Dungeon_Tileset.png";
}
} // namespace

Mapa::Mapa(Renderer& renderer, SectorTypeDto tipo, int ancho, int alto, unsigned int semilla) 
    : suelo(renderer, archivo_tileset(tipo)),
    borde(','),
    tipo(tipo),
    margen(0) {
    if (tipo == SectorTypeDto::FARM) {
        generar_granja(ancho, alto, semilla);
    } else if (tipo == SectorTypeDto::CAVERN) {
        generar_caverna(ancho, alto, semilla);
    }
}

void Mapa::generar_granja(int ancho, int alto, unsigned int semilla) {
    margen = 30;
    int ancho_total = ancho + 2 * margen;
    int alto_total = alto + 2 * margen;
    pasto_afuera.assign(alto_total, std::string(ancho_total, '.'));

    std::mt19937 azar(semilla);
    std::uniform_int_distribution<int> dado_x(0, ancho_total - 1);
    std::uniform_int_distribution<int> dado_y(0, alto_total - 1);
    std::uniform_int_distribution<int> dado_radio(1, 3);
    int manchas = ancho_total * alto_total / 25;
    for (int i = 0; i < manchas; ++i) {
        int centro_x = dado_x(azar);
        int centro_y = dado_y(azar);
        int radio = dado_radio(azar);
        for (int y = centro_y - radio; y <= centro_y + radio; ++y) {
            for (int x = centro_x - radio; x <= centro_x + radio; ++x) {
                int dx = x - centro_x;
                int dy = y - centro_y;
                bool adentro = x >= 0 && y >= 0 && x < ancho_total && y < alto_total && dx * dx + dy * dy <= radio * radio;
                if (adentro && dx * dx + dy * dy <= radio * radio) {
                    pasto_afuera[y][x] = ',';
                }
            }
        }
    }
    filas.clear();
    for (int y = 0; y < alto; y++) {
        filas.push_back(pasto_afuera[margen + y].substr(margen, ancho));
    }
}

void Mapa::generar_caverna(int ancho, int alto, unsigned int semilla) {
    borde = '#';

    filas.assign(alto, std::string(ancho, 'p'));

    std::mt19937 azar(semilla);
    std::uniform_int_distribution<int> dado(0, 9);
    for (int y = 0; y < alto; ++y) {
        for (int x = 0; x < ancho; ++x) {
            int numero = dado(azar);
            if (numero == 0) filas[y][x] = 'q';
            if (numero == 1) filas[y][x] = 'r';
        }
    }

    filas[0] = std::string(ancho, 'w');
    filas[1][ancho / 2] = 'e';
}

int Mapa::obtener_ancho() const {
  if (filas.empty()) {
    return 0;
  }
  return static_cast<int>(filas[0].size());
}

int Mapa::obtener_alto() const { return static_cast<int>(filas.size()); }

bool Mapa::es_escalera(int x, int y) const {
    return tile_en(x, y) == 'e';
}

char Mapa::tile_en(int x, int y) const {
    if (x >= 0 && x < obtener_ancho() && y >= 0 && y < obtener_alto()) {
        return filas[y][x];
    }
    int afuera_x = x + margen;
    int afuera_y = y + margen;
    if (!pasto_afuera.empty() && afuera_x >= 0 && afuera_y >= 0 && afuera_y < static_cast<int>(pasto_afuera.size()) && afuera_x < static_cast<int>(pasto_afuera[0].size())) {
        return pasto_afuera[afuera_y][afuera_x];
    }
    return borde;
}

void Mapa::dibujar_completo(Renderer& renderer, int origen_x, int origen_y, int lado) {
    for (int fila = 0; fila < obtener_alto(); fila++) {
        for (int columna = 0; columna < obtener_ancho(); columna++) {
            int x = origen_x + columna * lado;
            int y = origen_y + fila * lado;
            dibujar_tile(renderer, filas[fila][columna], x, y, lado);
        }
    }
}

void Mapa::dibujar_tile(Renderer& renderer, char tipo, int x, int y, int lado) {
    int columna = 4;
    int fila = 9;
    if (tipo == '#') {columna = 8; fila = 7;}
    if (tipo == ',') {columna = 1; fila = 9;}
    if (tipo == 'T') {columna = 1; fila = 4;}
    if (tipo == 'X') {columna = 4; fila = 4;}
    if (tipo == 'p') {columna = 6; fila = 1;}
    if (tipo == 'q') {columna = 7; fila = 0;}
    if (tipo == 'r') {columna = 9; fila = 2;}
    if (tipo == 'w') {columna = 2; fila = 0;}
    if (tipo == 'e') {columna = 9; fila = 3;}

  Rect origen(columna * TILE_SHEET, fila * TILE_SHEET, TILE_SHEET, TILE_SHEET);
  Rect destino(x, y, lado, lado);
  renderer.Copy(suelo, origen, destino);
}

void Mapa::dibujar(Renderer &renderer, int camara_x, int camara_y,
                   int ancho_ventana, int alto_ventana) {
  int primera_columna = tile_de_pixel(camara_x);
  int primera_fila = tile_de_pixel(camara_y);
  int ultima_columna = tile_de_pixel(camara_x + ancho_ventana);
  int ultima_fila = tile_de_pixel(camara_y + alto_ventana);

  for (int fila = primera_fila; fila <= ultima_fila; ++fila) {
    for (int columna = primera_columna; columna <= ultima_columna; ++columna) {
      int x = columna * TILE - camara_x;
      int y = fila * TILE - camara_y;
            bool afuera = columna < 0 || fila < 0 || columna >= obtener_ancho() || fila >= obtener_alto();
            if (afuera) {
                suelo.SetColorMod(150, 150, 150);
            }
      dibujar_tile(renderer, tile_en(columna, fila), x, y, TILE);
            if (afuera) {
                suelo.SetColorMod(255, 255, 255);
            }
    }    
  }
}
