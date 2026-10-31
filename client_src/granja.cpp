#include "granja.h"

#include <SDL2/SDL.h>

using namespace SDL2pp;

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
} // namespace

Granja::Granja(Renderer &renderer)
    // Cargar texturas
    : casas(renderer, "assets/edificios/House.png"),
      vaca(renderer, "assets/animales/Female Cow Brown.png"),
      gallina(renderer, "assets/animales/Chicken Blonde  Green.png"),
      cultivos(renderer, "assets/cultivos/Spring Crops.png"),
      suelo(renderer, "assets/mapas/ground_01_16x16.png"), vueltas(0) {

  // Por ahora fijos
  // Hacer después con servidor
  lista_casas.push_back({2, 1, 0});
  lista_casas.push_back({12, 2, 1});

  lista_animales.push_back({VACA, 4, 14, false});
  lista_animales.push_back({VACA, 8, 15, true});
  lista_animales.push_back({GALLINA, 13, 11, false});
  lista_animales.push_back({GALLINA, 15, 12, true});
  lista_animales.push_back({GALLINA, 14, 14, false});

  for (int tipo = FRUTILLA; tipo <= CALABAZA; tipo++) {
    for (int columna = 0; columna < 4; columna++) {
      int etapa = columna * ULTIMA_ETAPA[tipo] / 3;
      lista_cultivos.push_back(
          {static_cast<TipoCultivo>(tipo), 3 + columna, 8 + tipo, etapa});
    }
  }
}

void Granja::animar(long vueltas_pasadas) { vueltas += vueltas_pasadas; }

void Granja::dibujar_casa(Renderer &renderer, const Casa &casa, int camara_x,
                          int camara_y) {
  const SDL_Rect &modelo = MODELOS_CASAS[casa.modelo];
  Rect origen(modelo.x, modelo.y, modelo.w, modelo.h);

  int x = casa.tile_x * TILE - camara_x;
  int y = casa.tile_y * TILE - camara_y;
  Rect destino(x, y, modelo.w * ESCALA, modelo.h * ESCALA);
  renderer.Copy(casas, origen, destino);
}

void Granja::dibujar_cultivo(Renderer &renderer, const Cultivo &cultivo,
                             int camara_x, int camara_y) {
  int x = cultivo.tile_x * TILE - camara_x;
  int y = cultivo.tile_y * TILE - camara_y;
  Rect destino(x, y, TILE, TILE);

  Rect origen_tierra(ARADA_X, ARADA_Y, CULTIVO_LADO, CULTIVO_LADO);
  renderer.Copy(suelo, origen_tierra, destino);

  int fila = cultivo.tipo * 2 + 1;
  Rect origen_planta(cultivo.etapa * CULTIVO_LADO, fila * CULTIVO_LADO,
                     CULTIVO_LADO, CULTIVO_LADO);
  renderer.Copy(cultivos, origen_planta, destino);
}

void Granja::dibujar_animal(Renderer &renderer, const Animal &animal,
                            int camara_x, int camara_y) {
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
    int x = animal.tile_x * TILE - TILE / 2 - camara_x;
    int y = animal.tile_y * TILE - TILE - camara_y;
    Rect destino(x, y, VACA_LADO * ESCALA, VACA_LADO * ESCALA);
    renderer.Copy(vaca, origen, destino, 0.0, NullOpt, flip);
  } else {
    Rect origen(cuadro * GALLINA_LADO, 0, GALLINA_LADO, GALLINA_LADO);
    int x = animal.tile_x * TILE - camara_x;
    int y = animal.tile_y * TILE - camara_y;
    Rect destino(x, y, GALLINA_LADO * ESCALA, GALLINA_LADO * ESCALA);
    renderer.Copy(gallina, origen, destino, 0.0, NullOpt, flip);
  }
}

void Granja::dibujar(Renderer &renderer, int camara_x, int camara_y) {
  for (const Cultivo &cultivo : lista_cultivos) {
    dibujar_cultivo(renderer, cultivo, camara_x, camara_y);
  }
  for (const Casa &casa : lista_casas) {
    dibujar_casa(renderer, casa, camara_x, camara_y);
  }

  for (const Animal &animal : lista_animales) {
    dibujar_animal(renderer, animal, camara_x, camara_y);
  }
}