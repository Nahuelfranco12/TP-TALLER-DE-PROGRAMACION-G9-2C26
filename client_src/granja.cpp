#include "granja.h"

#include <SDL2/SDL.h>

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {
const int ESCALA = 4;
const int TILE = 16 * ESCALA;

// En House.png hay dos edificios enteros
const SDL_Rect MODELOS_CASAS[2] = {
    {144, 0, 80, 104},
    {0, 0, 80, 96},
};

// La vaca mide 32x32 y la gallina 16x16
const int VACA_LADO = 32;
const int GALLINA_LADO = 16;
const int CUADROS_ANIMACION = 4;
const long VUELTAS_POR_CUADRO_ANIMAL = 20; // 20 x 16 ms = 0.3 s

const int CULTIVO_LADO = 16;
const int ULTIMA_ETAPA[4] = {5, 5, 6, 5};

const int ARADA_X = 4 * 16;
const int ARADA_Y = 4 * 16;

const int ENTRADA_MINA_X = 10;
const int ENTRADA_MINA_Y = 1;
const int ESCALERA_COLUMNA = 9;
const int ESCALERA_FILA = 3;
} // namespace

Granja::Granja(Renderer &renderer)
    // Cargar texturas
    : casas(renderer, "assets/edificios/House.png"),
      vaca(renderer, "assets/animales/Female Cow Brown.png"),
      gallina(renderer, "assets/animales/Chicken Blonde  Green.png"),
      cultivos(renderer, "assets/cultivos/Spring Crops.png"),
      suelo(renderer, "assets/mapas/ground_01_16x16.png"),
      tileset_caverna(renderer, "assets/mapas/Dungeon_Tileset.png"),
      vueltas(0) {

  // Por ahora fijos
  // Hacer después con servidor
  lista_casas.push_back({2, 1, 0});

  lista_animales.push_back({VACA, 4, 14, false});
  lista_animales.push_back({VACA, 8, 15, true});
  lista_animales.push_back({GALLINA, 13, 11, false});
  lista_animales.push_back({GALLINA, 15, 12, true});
  lista_animales.push_back({GALLINA, 14, 14, false});

  for (int tipo = FRUTILLA; tipo <= PAPA; tipo++) {
    for (int columna = 0; columna < 4; columna++) {
      int etapa = columna * ULTIMA_ETAPA[tipo] / 3;
      lista_cultivos.push_back(
          {static_cast<TipoCultivo>(tipo), 3 + columna, 8 + tipo, etapa});
    }
  }
}

void Granja::animar(long vueltas_pasadas) { vueltas += vueltas_pasadas; }

void Granja::dibujar_casa(Renderer &renderer, const Casa &casa, int camara_x,
                          int camara_y, int lado) {
  const SDL_Rect &modelo = MODELOS_CASAS[casa.modelo];
  Rect origen(modelo.x, modelo.y, modelo.w, modelo.h);

  int x = casa.tile_x * lado - camara_x;
  int y = casa.tile_y * lado - camara_y;
  Rect destino(x, y, modelo.w * lado / 16, modelo.h * lado / 16);
  renderer.Copy(casas, origen, destino);
}

void Granja::dibujar_cultivo(Renderer &renderer, const Cultivo &cultivo,
                             int camara_x, int camara_y, int lado) {
  int x = cultivo.tile_x * lado - camara_x;
  int y = cultivo.tile_y * lado - camara_y;
  Rect destino(x, y, lado, lado);

  Rect origen_tierra(ARADA_X, ARADA_Y, CULTIVO_LADO, CULTIVO_LADO);
  renderer.Copy(suelo, origen_tierra, destino);

  int fila = cultivo.tipo * 2 + 1;
  Rect origen_planta(cultivo.etapa * CULTIVO_LADO, fila * CULTIVO_LADO,
                     CULTIVO_LADO, CULTIVO_LADO);
  renderer.Copy(cultivos, origen_planta, destino);
}

void Granja::dibujar_animal(Renderer &renderer, const Animal &animal,
                            int camara_x, int camara_y, int lado) {
  // Cuadro de la animación (0, 1, 2, 3, 0, 1, ...)
  int cuadro = static_cast<int>((vueltas / VUELTAS_POR_CUADRO_ANIMAL) %
                                CUADROS_ANIMACION);

  int flip = SDL_FLIP_NONE;
  if (animal.mira_a_la_izquierda) {
    flip = SDL_FLIP_HORIZONTAL;
  }

  if (animal.tipo == VACA) {
    // La vaca ocupa 2x2 tiles y l anclo por los pies
    Rect origen(cuadro * VACA_LADO, 0, VACA_LADO, VACA_LADO);
    int x = animal.tile_x * lado - lado / 2 - camara_x;
    int y = animal.tile_y * lado - lado - camara_y;
    Rect destino(x, y, VACA_LADO * lado / 16, VACA_LADO * lado / 16);
    renderer.Copy(vaca, origen, destino, 0.0, NullOpt, flip);
  } else {
    Rect origen(cuadro * GALLINA_LADO, 0, GALLINA_LADO, GALLINA_LADO);
    int x = animal.tile_x * lado - camara_x;
    int y = animal.tile_y * lado - camara_y;
    Rect destino(x, y, GALLINA_LADO * lado / 16, GALLINA_LADO * lado / 16);
    renderer.Copy(gallina, origen, destino, 0.0, NullOpt, flip);
  }
}

void Granja::dibujar(Renderer &renderer, int camara_x, int camara_y, int lado) {
  for (const Cultivo &cultivo : lista_cultivos) {
    dibujar_cultivo(renderer, cultivo, camara_x, camara_y, lado);
  }
  for (const Casa &casa : lista_casas) {
    dibujar_casa(renderer, casa, camara_x, camara_y, lado);
  }

  Rect origen_escalera(ESCALERA_COLUMNA * 16, ESCALERA_FILA * 16, 16, 16);
  Rect destino_escalera(ENTRADA_MINA_X * lado - camara_x,
                        ENTRADA_MINA_Y * lado - camara_y, lado, lado);
  renderer.Copy(tileset_caverna, origen_escalera, destino_escalera);

  for (const Animal &animal : lista_animales) {
    dibujar_animal(renderer, animal, camara_x, camara_y, lado);
  }
}

bool Granja::es_entrada_mina(int x, int y) {
  return x == ENTRADA_MINA_X && y == ENTRADA_MINA_Y;
}
