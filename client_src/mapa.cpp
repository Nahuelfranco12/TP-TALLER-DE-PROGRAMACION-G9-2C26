#include "mapa.h"

#include <random>

using namespace SDL2pp;

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
}

Mapa::Mapa(Renderer& renderer, int ancho, int alto, unsigned int semilla) : suelo(renderer, "assets/mapas/ground_01_16x16.png") {

    // Pasto claro
    filas.assign(alto, std::string(ancho, '.'));

    // Generar un mapa aleatorio de árboles y piedras
    std::mt19937 azar(semilla);
    std::uniform_int_distribution<int> columna_al_azar(0, ancho - 1);
    std::uniform_int_distribution<int> fila_al_azar(0, alto - 1);
    std::uniform_int_distribution<int> radio_al_azar(1, 3);

    // Manchas redondas de pasto oscuro
    const int CANTIDAD_MANCHAS = ancho * alto / 25;
    for (int i = 0; i < CANTIDAD_MANCHAS; ++i) {
        int centro_x = columna_al_azar(azar);
        int centro_y = fila_al_azar(azar);
        int radio = radio_al_azar(azar);
        for (int y = centro_y - radio; y <= centro_y + radio; ++y) {
            for (int x = centro_x - radio; x <= centro_x + radio; ++x) {
                bool dentro = x >= 0 && y >= 0 && x < ancho && y < alto;
                int dx = x - centro_x;
                int dy = y - centro_y;
                if (dentro && dx * dx + dy * dy <= radio * radio) {
                    filas[y][x] = ',';
                }
            }
        }
    }    
}

int Mapa::obtener_ancho() const {
    if (filas.empty()) {
        return 0;
    }
    return static_cast<int>(filas[0].size());
}

int Mapa::obtener_alto() const {
    return static_cast<int>(filas.size());
}

char Mapa::tile_en(int x, int y) const {
    if (x < 0 || y < 0 || x >= obtener_ancho() || y >= obtener_alto()) {
        return BORDE;
    }
    return filas[y][x];
}

void Mapa::dibujar_tile(Renderer& renderer, char tipo, int x, int y) {
    int columna = 4;
    int fila = 9;
    if (tipo == ',') {columna = 1; fila = 9;}
    if (tipo == 'T') {columna = 1; fila = 4;}
    if (tipo == 'X') {columna = 4; fila = 4;}
    if (tipo == 'B') {columna = 0; fila = 12;}

    Rect origen(columna * TILE_SHEET, fila * TILE_SHEET, TILE_SHEET, TILE_SHEET);
    Rect destino(x, y, TILE, TILE);
    renderer.Copy(suelo, origen, destino);
}

void Mapa::dibujar(Renderer& renderer, int camara_x, int camara_y, int ancho_ventana, int alto_ventana) {
    int primera_columna = tile_de_pixel(camara_x);
    int primera_fila = tile_de_pixel(camara_y);
    int ultima_columna = tile_de_pixel(camara_x + ancho_ventana);
    int ultima_fila = tile_de_pixel(camara_y + alto_ventana);

    for (int fila = primera_fila; fila <= ultima_fila; ++fila) {
        for (int columna = primera_columna; columna <= ultima_columna; ++columna) {
            int x = columna * TILE - camara_x;
            int y = fila * TILE - camara_y;
            dibujar_tile(renderer, tile_en(columna, fila), x, y);
        }
    }
}