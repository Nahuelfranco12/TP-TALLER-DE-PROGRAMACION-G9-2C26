#include "caverna.h"

using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {
const int MINERAL_ANCHO = 32;
const int MINERAL_ALTO = 28;
const int GOLPES_PARA_ROMPER = 3;
} // namespace

Caverna::Caverna(Renderer &renderer)
    : minerales(renderer, "assets/caverna/ore.png") {
  // Inicializar la lista de minerales con algunos ejemplos
  lista_minerales.push_back({HIERRO, 6, 7, 0});
  lista_minerales.push_back({CARBON, 13, 6, 0});
  lista_minerales.push_back({LAPISLAZULI, 8, 12, 0});
  lista_minerales.push_back({ORO, 12, 11, 0});
  lista_minerales.push_back({HIERRO, 4, 14, 0});
  lista_minerales.push_back({CARBON, 15, 15, 0});
  lista_minerales.push_back({ORO, 11, 9, 0});
}

bool Caverna::picar(int tile_x, int tile_y) {
  for (size_t i = 0; i < lista_minerales.size(); i++) {
    Mineral &mineral = lista_minerales[i];
    if (mineral.tile_x == tile_x && mineral.tile_y == tile_y) {
      mineral.golpes++;
      if (mineral.golpes >= GOLPES_PARA_ROMPER) {
        int tipo = mineral.tipo;
        lista_minerales.erase(lista_minerales.begin() + static_cast<long>(i));
        return tipo;
      }
      return -1;
    }
  }
  return -1;
}

void Caverna::dibujar(Renderer &renderer, int camara_x, int camara_y,
                      int lado) {
  for (const Mineral &mineral : lista_minerales) {
    Rect origen(mineral.golpes * MINERAL_ANCHO, mineral.tipo * MINERAL_ANCHO,
                MINERAL_ANCHO, MINERAL_ALTO);
    int x = mineral.tile_x * lado - camara_x;
    int y = mineral.tile_y * lado - camara_y;
    Rect destino(x, y, lado, MINERAL_ALTO * lado / MINERAL_ANCHO);
    renderer.Copy(minerales, origen, destino);
  }
}
