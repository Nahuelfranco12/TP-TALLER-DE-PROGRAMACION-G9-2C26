#include "caverna.h"

using SDL2pp::Rect;
using SDL2pp::Renderer;

Caverna::Caverna(Renderer &renderer)
    : minerales(renderer, RUTA_MINERALES), vueltas(0) {}

void Caverna::actualizar(
    const std::map<GamePositionDto, EntityDto> &entidades) {
  lista_minerales.clear();
  for (const auto &[pos, entidad] : entidades) {
    TipoMineral tipo;
    switch (entidad.type) {
    case EntityTypeDto::MINERAL_IRON:
      tipo = HIERRO;
      break;
    case EntityTypeDto::MINERAL_COAL:
      tipo = CARBON;
      break;
    case EntityTypeDto::MINERAL_LAPIZLAZULI:
      tipo = LAPISLAZULI;
      break;
    case EntityTypeDto::MINERAL_GOLD:
      tipo = ORO;
      break;
    default:
      continue;
    }

    size_t golpes = entidad.mineral.remainingHits;
    size_t etapa = SPRITE_MINERAL_ETAPA_ENTERO;
    if (golpes == CAVERNA_GOLPES_GOLPEADO) {
      etapa = SPRITE_MINERAL_ETAPA_GOLPEADO;
    } else if (golpes == CAVERNA_GOLPES_CASI_ROTO) {
      etapa = SPRITE_MINERAL_ETAPA_CASI_ROTO;
    }

    lista_minerales.push_back(
        {tipo, static_cast<int>(pos.x), static_cast<int>(pos.y), etapa});
  }
}

void Caverna::animar(long vueltas_pasadas) { vueltas += vueltas_pasadas; }

void Caverna::dibujar_mineral(Renderer &renderer, const Mineral &mineral,
                              int camara_x, int camara_y, int lado) {
  Rect origen(mineral.golpes * SPRITE_MINERAL_CELDA,
              mineral.tipo * SPRITE_MINERAL_CELDA, SPRITE_MINERAL_ANCHO,
              SPRITE_MINERAL_ALTO);
  int x = mineral.tile_x * lado - camara_x;
  int y = mineral.tile_y * lado - camara_y;
  int alto = SPRITE_MINERAL_ALTO * lado / SPRITE_MINERAL_ANCHO;
  Rect destino(x, y, lado, alto);
  renderer.Copy(minerales, origen, destino);
}

void Caverna::dibujar(Renderer &renderer, int camara_x, int camara_y,
                      int lado) {
  for (const Mineral &mineral : lista_minerales) {
    dibujar_mineral(renderer, mineral, camara_x, camara_y, lado);
  }
}
