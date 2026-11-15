#include "caverna.h"

using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {
const int MINERAL_ANCHO = 32;
const int MINERAL_ALTO = 28;
const int GOLPES_PARA_ROMPER = 3;

struct FormatoEnemigo {
  int lado;
  int pie;
};

const FormatoEnemigo FORMATO_ESQUELETO{32, 29};
const FormatoEnemigo FORMATO_ORCO{100, 57};

const int PIXELES_POR_TILE = 16;

const int VUELTAS_POR_CUADRO_ENEMIGO = 6;
}

Caverna::Caverna(Renderer &renderer)
  : minerales(renderer, "assets/caverna/ore.png"),
  esqueleto(renderer, "assets/enemigos/enemies-skeleton1_idle.png"),
  orco_quieto(renderer, "assets/enemigos/enemies-orc1_idle.png"),
  vueltas(0) {}

void Caverna::actualizar(const std::map<GamePositionDto, EntityDto> &entidades) {
  lista_minerales.clear();
  lista_enemigos.clear();
  for (const auto &[pos, entidad] : entidades) {
    if (entidad.type == EntityTypeDto::SKELETON) {
      lista_enemigos.push_back({ESQUELETO, static_cast<int>(pos.x), static_cast<int>(pos.y), entidad.enemy.alive});
      continue;
    } else if (entidad.type == EntityTypeDto::ORC) {
      lista_enemigos.push_back({ORCO, static_cast<int>(pos.x), static_cast<int>(pos.y), entidad.enemy.alive});
      continue;
    }

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
    size_t etapa = 0;
    if (golpes == 2) {
      etapa = 1;
    } else if (golpes == 1) {
      etapa = 2;
    }

    lista_minerales.push_back({
      tipo,
      static_cast<int>(pos.x),
      static_cast<int>(pos.y),
      etapa
    });
  }
}

void Caverna::animar(long vueltas_pasadas) {vueltas += vueltas_pasadas;}

void Caverna::dibujar_mineral(Renderer &renderer, const Mineral &mineral, int camara_x, int camara_y, int lado) {
  Rect origen(mineral.golpes * MINERAL_ANCHO, mineral.tipo * MINERAL_ANCHO, MINERAL_ANCHO, MINERAL_ALTO);
  int x = mineral.tile_x * lado - camara_x;
  int y = mineral.tile_y * lado - camara_y;
  Rect destino(x, y, lado, MINERAL_ALTO * lado / MINERAL_ANCHO);
  renderer.Copy(minerales, origen, destino);
}

void Caverna::dibujar_enemigo(Renderer &renderer, const Enemigo &enemigo, int camara_x, int camara_y, int lado) {
  if(!enemigo.vivo) 
    return;
  
  SDL2pp::Texture *textura = &esqueleto;
  FormatoEnemigo formato = FORMATO_ESQUELETO;
  switch (enemigo.tipo) {
  case ESQUELETO:
    textura = &esqueleto;
    formato = FORMATO_ESQUELETO;
    break;
  
  case ORCO:
    textura = &orco_quieto;
    formato = FORMATO_ORCO;
    break;
  }

  int cuadros = textura->GetWidth() / formato.lado;
  int cuadro = static_cast<int>((vueltas / VUELTAS_POR_CUADRO_ENEMIGO) % cuadros);

  Rect origen(cuadro * formato.lado, 0, formato.lado, formato.lado);

  int tamanio = formato.lado * lado / PIXELES_POR_TILE;

  int x = enemigo.tile_x * lado + lado / 2 - tamanio / 2 - camara_x;
  int y = enemigo.tile_y * lado + lado - formato.pie * lado / PIXELES_POR_TILE - camara_y;

  renderer.Copy(*textura, origen, Rect(x, y, tamanio, tamanio));

}

void Caverna::dibujar(Renderer &renderer, int camara_x, int camara_y, int lado) {
  for (const Mineral &mineral : lista_minerales) {
    dibujar_mineral(renderer, mineral, camara_x, camara_y, lado);
  }
  for (const Enemigo &enemigo : lista_enemigos) {
    dibujar_enemigo(renderer, enemigo, camara_x, camara_y, lado);
  }
}