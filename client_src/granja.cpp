#include "granja.h"

#include <SDL2/SDL.h>

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {
// En House.png hay dos edificios enteros
const SDL_Rect MODELOS_CASAS[] = SPRITE_MODELOS_CASAS;

const int ULTIMA_ETAPA[] = CULTIVO_ULTIMA_ETAPA;
} // namespace

Granja::Granja(Renderer &renderer)
    // Cargar texturas
    : casas(renderer, RUTA_CASAS), vaca(renderer, RUTA_VACA),
      gallina(renderer, RUTA_GALLINA), cultivos(renderer, RUTA_CULTIVOS),
      suelo(renderer, RUTA_TILESET_GRANJA), huevo(renderer, RUTA_HUEVO),
      leche(renderer, RUTA_LECHE), vueltas(0) {

  // Por ahora fijos
  // Hacer después con servidor
  lista_casas.push_back(
      {GRANJA_CASA_TILE_X, GRANJA_CASA_TILE_Y, GRANJA_CASA_MODELO});
}

void Granja::animar(long vueltas_pasadas) { vueltas += vueltas_pasadas; }

void Granja::dibujar_casa(Renderer &renderer, const Casa &casa, int camara_x,
                          int camara_y, int lado) {
  const SDL_Rect &modelo = MODELOS_CASAS[casa.modelo];
  Rect origen(modelo.x, modelo.y, modelo.w, modelo.h);

  int x = casa.tile_x * lado - camara_x;
  int y = casa.tile_y * lado - camara_y;
  Rect destino(x, y, modelo.w * lado / TAMANIO_TILE_ASSET,
               modelo.h * lado / TAMANIO_TILE_ASSET);
  renderer.Copy(casas, origen, destino);
}

void Granja::dibujar_cultivo(Renderer &renderer, const Cultivo &cultivo,
                             int camara_x, int camara_y, int lado) {
  int x = cultivo.tile_x * lado - camara_x;
  int y = cultivo.tile_y * lado - camara_y;
  Rect destino(x, y, lado, lado);

  Rect origen_tierra(SUELO_ARADO_COLUMNA * TAMANIO_TILE_ASSET,
                     SUELO_ARADO_FILA * TAMANIO_TILE_ASSET, TAMANIO_TILE_ASSET,
                     TAMANIO_TILE_ASSET);
  renderer.Copy(suelo, origen_tierra, destino);

  int fila =
      cultivo.tipo * SPRITE_CULTIVO_FILAS_POR_TIPO + SPRITE_CULTIVO_FILA_PLANTA;
  Rect origen_planta(cultivo.etapa * SPRITE_CULTIVO_LADO,
                     fila * SPRITE_CULTIVO_LADO, SPRITE_CULTIVO_LADO,
                     SPRITE_CULTIVO_LADO);
  renderer.Copy(cultivos, origen_planta, destino);
}

void Granja::dibujar_animal(Renderer &renderer, const Animal &animal,
                            int camara_x, int camara_y, int lado) {
  // Cuadro de la animación (0, 1, 2, 3, 0, 1, ...)
  int cuadro = static_cast<int>((vueltas / ANIMAL_VUELTAS_POR_CUADRO) %
                                ANIMAL_CUADROS_ANIMACION);

  int flip = SDL_FLIP_NONE;
  if (animal.mira_a_la_izquierda) {
    flip = SDL_FLIP_HORIZONTAL;
  }

  if (animal.tipo == VACA) {
    // La vaca ocupa 2x2 tiles y l anclo por los pies
    Rect origen(cuadro * SPRITE_VACA_LADO, 0, SPRITE_VACA_LADO,
                SPRITE_VACA_LADO);
    int x = animal.tile_x * lado - lado / 2 - camara_x;
    int y = animal.tile_y * lado - lado - camara_y;
    int lado_vaca = SPRITE_VACA_LADO * lado / TAMANIO_TILE_ASSET;
    Rect destino(x, y, lado_vaca, lado_vaca);
    renderer.Copy(vaca, origen, destino, 0.0, NullOpt, flip);
    if (animal.listo) {
      dibujar_producto(renderer, leche, x + destino.w / 2, y, lado);
    }
  } else {
    Rect origen(cuadro * SPRITE_GALLINA_LADO, 0, SPRITE_GALLINA_LADO,
                SPRITE_GALLINA_LADO);
    int x = animal.tile_x * lado - camara_x;
    int y = animal.tile_y * lado - camara_y;
    int lado_gallina = SPRITE_GALLINA_LADO * lado / TAMANIO_TILE_ASSET;
    Rect destino(x, y, lado_gallina, lado_gallina);
    renderer.Copy(gallina, origen, destino, 0.0, NullOpt, flip);
    if (animal.listo) {
      dibujar_producto(renderer, huevo, x + destino.w / 2, y, lado);
    }
  }
}

void Granja::dibujar(Renderer &renderer, int camara_x, int camara_y, int lado) {
  for (const Cultivo &cultivo : lista_cultivos) {
    dibujar_cultivo(renderer, cultivo, camara_x, camara_y, lado);
  }
  for (const Casa &casa : lista_casas) {
    dibujar_casa(renderer, casa, camara_x, camara_y, lado);
  }

  for (const Animal &animal : lista_animales) {
    dibujar_animal(renderer, animal, camara_x, camara_y, lado);
  }
}

void Granja::actualizar(const std::map<GamePositionDto, EntityDto> &entidades) {
  lista_animales.clear();
  lista_cultivos.clear();
  for (const auto &[pos, entidad] : entidades) {
    int x = static_cast<int>(pos.x);
    int y = static_cast<int>(pos.y);
    if (entidad.type == EntityTypeDto::COW) {
      lista_animales.push_back({VACA, x, y, false, entidad.ready});
    } else if (entidad.type == EntityTypeDto::CHICKEN) {
      lista_animales.push_back({GALLINA, x, y, false, entidad.ready});
    } else if (entidad.type == EntityTypeDto::CROP) {
      TipoCultivo tipo = static_cast<TipoCultivo>(entidad.crop.type);
      int etapa = static_cast<int>(entidad.crop.growth) * ULTIMA_ETAPA[tipo] /
                  CULTIVO_CRECIMIENTO_MAXIMO;
      lista_cultivos.push_back({tipo, x, y, etapa});
    }
  }
}

void Granja::dibujar_producto(SDL2pp::Renderer &renderer,
                              SDL2pp::Texture &producto, int centro_x,
                              int arriba_y, int lado) {
  int ancho = producto.GetWidth() * lado / ICONO_PIXELES_POR_TILE;
  int alto = producto.GetHeight() * lado / ICONO_PIXELES_POR_TILE;

  int salto = 0;
  if ((vueltas / PRODUCTO_VUELTAS_POR_SALTO) % 2 == 1) {
    salto = PRODUCTO_SALTO * lado / TAMANIO_TILE_ASSET;
  }

  Rect destino(centro_x - ancho / 2, arriba_y - alto - salto, ancho, alto);
  renderer.Copy(producto, NullOpt, destino);
}
