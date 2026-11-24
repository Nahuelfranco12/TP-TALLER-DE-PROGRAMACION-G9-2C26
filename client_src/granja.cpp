#include "granja.h"

#include <SDL2/SDL.h>

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {
// En House.png hay dos edificios enteros
const SDL_Rect MODELOS_CASAS[] = SPRITE_MODELOS_CASAS;

bool modelo_de_cabana(BuildingTypeDto tipo, int &modelo) {
  switch (tipo) {
    case BuildingTypeDto::CABIN_PLAYER_1:
      modelo = 0;
      return true;
    case BuildingTypeDto::CABIN_PLAYER_2:
      modelo = 1;
      return true;
    case BuildingTypeDto::CABIN_PLAYER_3:
      modelo = 2;
      return true;
    case BuildingTypeDto::CABIN_PLAYER_4:
      modelo = 3;
      return true;
    case BuildingTypeDto::CABIN_PLAYER_5:
      modelo = 4;
      return true;
    default:
      return false;
  }
}

const int ULTIMA_ETAPA[] = CULTIVO_ULTIMA_ETAPA;
} // namespace

Granja::Granja(Renderer &renderer)
    // Cargar texturas
    : casas(renderer, RUTA_TILESET_CABANAS), vaca(renderer, RUTA_VACA),
      gallina(renderer, RUTA_GALLINA), cultivos(renderer, RUTA_CULTIVOS),
      suelo(renderer, RUTA_TILESET_GRANJA), huevo(renderer, RUTA_HUEVO),
      leche(renderer, RUTA_LECHE), cofre(renderer, RUTA_COFRE),
      interior(renderer, RUTA_INTERIOR), vueltas(0) {}

void Granja::animar(long vueltas_pasadas) { vueltas += vueltas_pasadas; }

void Granja::dibujar_casa(Renderer &renderer, const Casa &casa, int camara_x,
                          int camara_y, int lado) {
  const SDL_Rect &modelo = MODELOS_CASAS[casa.modelo];
  int ancho = casa.ancho * lado;
  int alto = modelo.h * ancho / modelo.w;
  int x = casa.tile_x * lado - camara_x;
  int pie = (casa.tile_y + casa.alto) * lado - camara_y;
  renderer.Copy(casas, Rect(modelo.x, modelo.y, modelo.w, modelo.h), Rect(x, pie - alto, ancho, alto));
}

void Granja::dibujar_cultivo(Renderer &renderer, const Cultivo &cultivo,
                             int camara_x, int camara_y, int lado) {
  int x = cultivo.tile_x * lado - camara_x;
  int y = cultivo.tile_y * lado - camara_y;
  Rect destino(x, y, lado, lado);

  Rect origen_tierra(SUELO_ARADO_COLUMNA * PIXELES_POR_TILE,
                     SUELO_ARADO_FILA * PIXELES_POR_TILE, PIXELES_POR_TILE,
                     PIXELES_POR_TILE);
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
    int lado_vaca = SPRITE_VACA_LADO * lado / PIXELES_POR_TILE;
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
    int lado_gallina = SPRITE_GALLINA_LADO * lado / PIXELES_POR_TILE;
    Rect destino(x, y, lado_gallina, lado_gallina);
    renderer.Copy(gallina, origen, destino, 0.0, NullOpt, flip);
    if (animal.listo) {
      dibujar_producto(renderer, huevo, x + destino.w / 2, y, lado);
    }
  }
}
void Granja::dibujar_mueble(Renderer &renderer, const Mueble &mueble,
                            int camara_x, int camara_y, int lado) {
  int x = mueble.tile_x * lado - camara_x;
  int y = mueble.tile_y * lado - camara_y;
  Rect destino(x, y, lado, lado);

  if (mueble.tipo == COFRE) {
    int fila = mueble.abierto ? SPRITE_COFRE_ABIERTO_Y : SPRITE_COFRE_CERRADO_Y;
    Rect origen(SPRITE_COFRE_X, fila, SPRITE_COFRE_LADO, SPRITE_COFRE_LADO);
    renderer.Copy(cofre, origen, destino);
  } else if (mueble.tipo == CAMA) {
    Rect origen(SPRITE_CAMA_X, SPRITE_CAMA_Y, SPRITE_CAMA_ANCHO, SPRITE_CAMA_ALTO);
    int ancho = SPRITE_CAMA_ANCHO * lado / PIXELES_POR_TILE;
    int alto = SPRITE_CAMA_ALTO * lado / PIXELES_POR_TILE;
    Rect destino(x + (lado - ancho) / 2, y + lado - alto, ancho, alto);
    renderer.Copy(interior, origen, destino);
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

  for (const Mueble &mueble : lista_muebles) {
    dibujar_mueble(renderer, mueble, camara_x, camara_y, lado);
  }
}

void Granja::actualizar(const std::map<GamePositionDto, EntityDto> &entidades) {
  lista_animales.clear();
  lista_cultivos.clear();
  lista_muebles.clear();
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
    } else if (entidad.type == EntityTypeDto::CHEST) {
      lista_muebles.push_back({COFRE, x, y, entidad.chest.openedByMe});
    } else if (entidad.type == EntityTypeDto::BED) {
      lista_muebles.push_back({CAMA, x, y, false});
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
    salto = PRODUCTO_SALTO * lado / PIXELES_POR_TILE;
  }

  Rect destino(centro_x - ancho / 2, arriba_y - alto - salto, ancho, alto);
  renderer.Copy(producto, NullOpt, destino);
}

void Granja::actualizar_edificios(const std::vector<BuildingDto> &del_servidor) {
  lista_casas.clear();
  for (const BuildingDto &edificio : del_servidor) {
    int modelo = 0;
    if (modelo_de_cabana(edificio.type, modelo)) {
      lista_casas.push_back({static_cast<int>(edificio.topLeft.x),
                            static_cast<int>(edificio.topLeft.y),
                            static_cast<int>(edificio.width),
                            static_cast<int>(edificio.height), modelo});
    }
  }
}
