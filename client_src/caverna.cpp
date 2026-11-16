#include "caverna.h"
#include "constantes_sdl.h"

#include <algorithm>
#include <cstdlib>

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {

struct FormatoEnemigo {
  int lado;
  int pie;
};

const FormatoEnemigo FORMATO_ESQUELETO{32, 29};
const FormatoEnemigo FORMATO_ORCO{100, 57};
const FormatoEnemigo FORMATO_VAMPIRO{32, 29};

const int PIXELES_POR_TILE = 16;

const int VUELTAS_POR_CUADRO_ENEMIGO = 6;

// Atacando tiene prioridad sobre caminando, y caminando sobre quieto
SDL2pp::Texture *elegir_textura(SDL2pp::Texture &quieto,
                                SDL2pp::Texture &caminando,
                                SDL2pp::Texture &atacando,
                                long vueltas_caminando, long vueltas_atacando) {
  if (vueltas_atacando > 0)
    return &atacando;
  if (vueltas_caminando > 0)
    return &caminando;
  return &quieto;
}
} // namespace

Caverna::Caverna(Renderer &renderer)
    : minerales(renderer, RUTA_MINERALES),
      esqueleto(renderer, RUTA_ESQUELETO_QUIETO),
      esqueleto_caminando(renderer, RUTA_ESQUELETO_CAMINANDO),
      esqueleto_atacando(renderer, RUTA_ESQUELETO_ATACA),
      orco_quieto(renderer, RUTA_ORCO_QUIETO),
      orco_caminando(renderer, RUTA_ORCO_CAMINANDO),
      orco_atacando(renderer, RUTA_ORCO_ATACA),
      vampiro_quieto(renderer, RUTA_VAMPIRO_QUIETO),
      vampiro_caminando(renderer, RUTA_VAMPIRO_CAMINANDO),
      vampiro_atacando(renderer, RUTA_VAMPIRO_ATACA), vueltas(0) {}

void Caverna::actualizar(
    const std::map<GamePositionDto, EntityDto> &entidades) {
  const std::vector<Enemigo> anteriores = lista_enemigos;
  lista_minerales.clear();
  lista_enemigos.clear();
  for (const auto &[pos, entidad] : entidades) {
    if (entidad.type == EntityTypeDto::SKELETON) {
      lista_enemigos.push_back({ESQUELETO, static_cast<int>(pos.x),
                                static_cast<int>(pos.y), entidad.enemy.alive, 0,
                                0, false});
      continue;
    } else if (entidad.type == EntityTypeDto::ORC) {
      lista_enemigos.push_back({ORCO, static_cast<int>(pos.x),
                                static_cast<int>(pos.y), entidad.enemy.alive, 0,
                                0, false});
      continue;
    } else if (entidad.type == EntityTypeDto::VAMPIRE_MALE ||
               entidad.type == EntityTypeDto::VAMPIRE_FEMALE) {
      TipoEnemigo tipo =
          entidad.type == EntityTypeDto::VAMPIRE_FEMALE ? VAMPIRA : VAMPIRO;
      lista_enemigos.push_back({tipo, static_cast<int>(pos.x),
                                static_cast<int>(pos.y), entidad.enemy.alive, 0,
                                0, false});
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
    size_t etapa = SPRITE_MINERAL_ETAPA_ENTERO;
    if (golpes == CAVERNA_GOLPES_GOLPEADO) {
      etapa = SPRITE_MINERAL_ETAPA_GOLPEADO;
    } else if (golpes == CAVERNA_GOLPES_CASI_ROTO) {
      etapa = SPRITE_MINERAL_ETAPA_CASI_ROTO;
    }

    lista_minerales.push_back(
        {tipo, static_cast<int>(pos.x), static_cast<int>(pos.y), etapa});
  }

  for (Enemigo &enemigo : lista_enemigos) {
    seguir_movimiento(enemigo, anteriores, lista_enemigos);
  }
}

bool Caverna::hay_enemigo(const std::vector<Enemigo> &lista, TipoEnemigo tipo,
                          int x, int y) {
  return std::any_of(
      lista.begin(), lista.end(), [tipo, x, y](const Enemigo &otro) {
        return otro.tipo == tipo && otro.tile_x == x && otro.tile_y == y;
      });
}

void Caverna::seguir_movimiento(Enemigo &enemigo,
                                const std::vector<Enemigo> &anteriores,
                                const std::vector<Enemigo> &actuales) {
  // El mismo enemigo, que no se movió: sigue como venía
  auto mismo = std::find_if(
      anteriores.begin(), anteriores.end(), [&enemigo](const Enemigo &otro) {
        return otro.tipo == enemigo.tipo && otro.tile_x == enemigo.tile_x &&
               otro.tile_y == enemigo.tile_y;
      });
  if (mismo != anteriores.end()) {
    enemigo.vueltas_caminando = mismo->vueltas_caminando;
    enemigo.vueltas_atacando = mismo->vueltas_atacando;
    enemigo.mira_izquierda = mismo->mira_izquierda;
    return;
  }

  // Uno del mismo tipo que estaba al lado y dejó su tile: se movió
  auto de_donde = std::find_if(
      anteriores.begin(), anteriores.end(),
      [&enemigo, &actuales](const Enemigo &otro) {
        int distancia = std::abs(otro.tile_x - enemigo.tile_x) +
                        std::abs(otro.tile_y - enemigo.tile_y);
        return otro.tipo == enemigo.tipo &&
               distancia == CAVERNA_ENEMIGO_DISTANCIA_PASO &&
               !hay_enemigo(actuales, otro.tipo, otro.tile_x, otro.tile_y);
      });
  if (de_donde == anteriores.end()) {
    return; // recién aparecido: queda quieto
  }

  enemigo.vueltas_caminando = CAVERNA_ENEMIGO_VUELTAS_CAMINANDO;
  enemigo.mira_izquierda = de_donde->mira_izquierda;
  if (enemigo.tile_x < de_donde->tile_x) {
    enemigo.mira_izquierda = true;
  } else if (enemigo.tile_x > de_donde->tile_x) {
    enemigo.mira_izquierda = false;
  }
}

void Caverna::golpearon_a(int tile_x, int tile_y) {
  for (Enemigo &enemigo : lista_enemigos) {
    int distancia =
        std::abs(enemigo.tile_x - tile_x) + std::abs(enemigo.tile_y - tile_y);
    if (!enemigo.vivo || distancia != CAVERNA_ENEMIGO_DISTANCIA_ATAQUE ||
        enemigo.vueltas_atacando > 0) {
      continue;
    }
    enemigo.vueltas_atacando = duracion_ataque(enemigo.tipo);
    // Se da vuelta para mirar al jugador
    if (tile_x < enemigo.tile_x) {
      enemigo.mira_izquierda = true;
    } else if (tile_x > enemigo.tile_x) {
      enemigo.mira_izquierda = false;
    }
  }
}

long Caverna::duracion_ataque(TipoEnemigo tipo) const {
  int cuadros = esqueleto_atacando.GetWidth() / FORMATO_ESQUELETO.lado;
  if (tipo == ORCO) {
    cuadros = orco_atacando.GetWidth() / FORMATO_ORCO.lado;
  } else if (tipo == VAMPIRO || tipo == VAMPIRA) {
    cuadros = vampiro_atacando.GetWidth() / FORMATO_VAMPIRO.lado;
  }
  return static_cast<long>(cuadros) * VUELTAS_POR_CUADRO_ENEMIGO;
}

void Caverna::animar(long vueltas_pasadas) {
  vueltas += vueltas_pasadas;
  for (Enemigo &enemigo : lista_enemigos) {
    if (enemigo.vueltas_caminando > 0) {
      enemigo.vueltas_caminando -= vueltas_pasadas;
    }
    if (enemigo.vueltas_atacando > 0) {
      enemigo.vueltas_atacando -= vueltas_pasadas;
    }
  }
}

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

void Caverna::dibujar_enemigo(Renderer &renderer, const Enemigo &enemigo,
                              int camara_x, int camara_y, int lado) {
  if (!enemigo.vivo)
    return;

  SDL2pp::Texture *textura = &esqueleto;
  FormatoEnemigo formato = FORMATO_ESQUELETO;
  int centro_x = SPRITE_ESQUELETO_CENTRO_X;
  switch (enemigo.tipo) {
  case ESQUELETO:
    textura =
        elegir_textura(esqueleto, esqueleto_caminando, esqueleto_atacando,
                       enemigo.vueltas_caminando, enemigo.vueltas_atacando);
    formato = FORMATO_ESQUELETO;
    centro_x = SPRITE_ESQUELETO_CENTRO_X;
    break;

  case ORCO:
    textura =
        elegir_textura(orco_quieto, orco_caminando, orco_atacando,
                       enemigo.vueltas_caminando, enemigo.vueltas_atacando);
    formato = FORMATO_ORCO;
    centro_x = SPRITE_ORCO_CENTRO_X;
    break;
  case VAMPIRO:
  case VAMPIRA:
    textura =
        elegir_textura(vampiro_quieto, vampiro_caminando, vampiro_atacando,
                       enemigo.vueltas_caminando, enemigo.vueltas_atacando);
    formato = FORMATO_VAMPIRO;
    centro_x = SPRITE_VAMPIRO_CENTRO_X;
    if (textura == &vampiro_caminando) {
      formato.pie = SPRITE_VAMPIRO_PIE_CAMINANDO;
    }
    break;
  }

  // Al espejar, el cuerpo cambia de lado dentro del cuadro
  int flip = SDL_FLIP_NONE;
  int correccion_x = 0;
  if (enemigo.mira_izquierda) {
    flip = SDL_FLIP_HORIZONTAL;
    correccion_x = (2 * centro_x - formato.lado) * lado / PIXELES_POR_TILE;
  }

  int cuadros = textura->GetWidth() / formato.lado;
  int cuadro =
      static_cast<int>((vueltas / VUELTAS_POR_CUADRO_ENEMIGO) % cuadros);
  if (enemigo.vueltas_atacando > 0) {
    long duracion = static_cast<long>(cuadros) * VUELTAS_POR_CUADRO_ENEMIGO;
    cuadro = static_cast<int>((duracion - enemigo.vueltas_atacando) /
                              VUELTAS_POR_CUADRO_ENEMIGO);
    cuadro = std::clamp(cuadro, 0, cuadros - 1);
  }

  Rect origen(cuadro * formato.lado, 0, formato.lado, formato.lado);

  int tamanio = formato.lado * lado / PIXELES_POR_TILE;

  int x = enemigo.tile_x * lado + lado / 2 - tamanio / 2 - camara_x;
  int y = enemigo.tile_y * lado + lado - formato.pie * lado / PIXELES_POR_TILE -
          camara_y;

  if (enemigo.tipo == VAMPIRA)
    textura->SetColorMod(255, 170, 200);
  renderer.Copy(*textura, origen, Rect(x + correccion_x, y, tamanio, tamanio),
                0.0, NullOpt, flip);
  textura->SetColorMod(255, 255, 255);
}

void Caverna::dibujar(Renderer &renderer, int camara_x, int camara_y,
                      int lado) {
  for (const Mineral &mineral : lista_minerales) {
    dibujar_mineral(renderer, mineral, camara_x, camara_y, lado);
  }
  for (const Enemigo &enemigo : lista_enemigos) {
    dibujar_enemigo(renderer, enemigo, camara_x, camara_y, lado);
  }
}
