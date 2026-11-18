#include "caverna.h"
#include "constantes_sdl.h"

#include <algorithm>
#include <cstdlib>

using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {

struct FormatoEnemigo {
  int lado;
  int pie;
};

const FormatoEnemigo FORMATO_CALAVERA{SPRITE_CALAVERA_LADO,
                                      SPRITE_CALAVERA_PIE};
// const FormatoEnemigo FORMATO_CALAVERA_VERDE{};
const FormatoEnemigo FORMATO_TRAMPA{SPRITE_TRAMPA_LADO, SPRITE_TRAMPA_PIE};

// const int PIXELES_POR_TILE = 16;

// const int VUELTAS_POR_CUADRO_ENEMIGO = 6;

const HojasEnemigo HOJAS_ESQUELETO{
    RUTA_ESQUELETO_QUIETO,    RUTA_ESQUELETO_CAMINANDO,
    RUTA_ESQUELETO_ATACA,     RUTA_ESQUELETO_DANIADO,
    RUTA_ESQUELETO_MUERTO,    SPRITE_ESQUELETO_LADO,
    SPRITE_ESQUELETO_PIE,     SPRITE_ESQUELETO_PIE,
    SPRITE_ESQUELETO_CENTRO_X};
const HojasEnemigo HOJAS_ORCO{
    RUTA_ORCO_QUIETO,  RUTA_ORCO_CAMINANDO, RUTA_ORCO_ATACA,
    RUTA_ORCO_DANIADO, RUTA_ORCO_MUERTO,    SPRITE_ORCO_LADO,
    SPRITE_ORCO_PIE,   SPRITE_ORCO_PIE,     SPRITE_ORCO_CENTRO_X};
const HojasEnemigo HOJAS_VAMPIRO{
    RUTA_VAMPIRO_QUIETO,    RUTA_VAMPIRO_CAMINANDO,
    RUTA_VAMPIRO_ATACA,     RUTA_VAMPIRO_DANIADO,
    RUTA_VAMPIRO_MUERTO,    SPRITE_VAMPIRO_LADO,
    SPRITE_VAMPIRO_PIE,     SPRITE_VAMPIRO_PIE_CAMINANDO,
    SPRITE_VAMPIRO_CENTRO_X};
} // namespace

Caverna::Caverna(Renderer &renderer)
    : minerales(renderer, RUTA_MINERALES),
      sprites_esqueleto(renderer, HOJAS_ESQUELETO),
      sprites_orco(renderer, HOJAS_ORCO),
      sprites_vampiro(renderer, HOJAS_VAMPIRO),
      calavera_azul_quieto(renderer, RUTA_CALAVERA_AZUL_QUIETA),
      calavera_verde_quieto(renderer, RUTA_CALAVERA_VERDE_QUIETA),
      pinches(renderer, RUTA_PINCHES),
      lanzallamas_1(renderer, RUTA_LANZALLAMAS1),
      lanzallamas_2(renderer, RUTA_LANZALLAMAS2), vueltas(0) {}

void Caverna::actualizar(
    const std::map<GamePositionDto, EntityDto> &entidades) {
  const std::vector<Enemigo> anteriores = lista_enemigos;
  lista_minerales.clear();
  lista_enemigos.clear();
  for (const auto &[pos, entidad] : entidades) {
    if (entidad.type == EntityTypeDto::SKELETON) {
      lista_enemigos.push_back({ESQUELETO,
                                static_cast<int>(pos.x),
                                static_cast<int>(pos.y),
                                entidad.enemy.alive,
                                {},
                                entidad.enemy.direction});
      continue;
    } else if (entidad.type == EntityTypeDto::ORC) {
      lista_enemigos.push_back({ORCO,
                                static_cast<int>(pos.x),
                                static_cast<int>(pos.y),
                                entidad.enemy.alive,
                                {},
                                entidad.enemy.direction});
      continue;
    } else if (entidad.type == EntityTypeDto::VAMPIRE_MALE ||
               entidad.type == EntityTypeDto::VAMPIRE_FEMALE) {
      TipoEnemigo tipo =
          entidad.type == EntityTypeDto::VAMPIRE_FEMALE ? VAMPIRA : VAMPIRO;
      lista_enemigos.push_back({tipo,
                                static_cast<int>(pos.x),
                                static_cast<int>(pos.y),
                                entidad.enemy.alive,
                                {},
                                entidad.enemy.direction});
      continue;
    } else if (entidad.type == EntityTypeDto::SKULL_BLUE) {
      lista_enemigos.push_back({CALAVERA_AZUL,
                                static_cast<int>(pos.x),
                                static_cast<int>(pos.y),
                                entidad.enemy.alive,
                                {},
                                entidad.enemy.direction});
      continue;
    } else if (entidad.type == EntityTypeDto::SKULL_GREEN) {
      lista_enemigos.push_back({CALAVERA_VERDE,
                                static_cast<int>(pos.x),
                                static_cast<int>(pos.y),
                                entidad.enemy.alive,
                                {},
                                entidad.enemy.direction});
      continue;
    } else if (entidad.type == EntityTypeDto::TRAP_PINCH) {
      lista_enemigos.push_back({TRAMPA_PINCHES,
                                static_cast<int>(pos.x),
                                static_cast<int>(pos.y),
                                true,
                                {},
                                entidad.enemy.direction});
      continue;
    } else if (entidad.type == EntityTypeDto::TRAP_FLAME) {
      lista_enemigos.push_back({TRAMPA_LANZALLAMAS,
                                static_cast<int>(pos.x),
                                static_cast<int>(pos.y),
                                true,
                                {},
                                entidad.enemy.direction});
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
    enemigo.animacion = mismo->animacion;
    SpritesEnemigo *sprites = sprites_de(enemigo.tipo);
    if (sprites != nullptr) {
      if (mismo->vivo && !enemigo.vivo) {
        enemigo.animacion.morir(sprites->duracion_muerte());
      } else if (!mismo->vivo && enemigo.vivo) {
        enemigo.animacion.revivir(sprites->duracion_muerte());
      }
    }
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
    return; // recién aparecido: quieto (o tirado, si llega muerto)
  }

  enemigo.animacion = de_donde->animacion;
  enemigo.animacion.caminar(enemigo.tile_x - de_donde->tile_x,
                            CAVERNA_ENEMIGO_VUELTAS_CAMINANDO);
}

SpritesEnemigo *Caverna::sprites_de(TipoEnemigo tipo) {
  switch (tipo) {
  case ESQUELETO:
    return &sprites_esqueleto;
  case ORCO:
    return &sprites_orco;
  case VAMPIRO:
  case VAMPIRA:
    return &sprites_vampiro;
  default:
    return nullptr; // calaveras y trampas: los dibuja su propio código
  }
}

void Caverna::golpear(int tile_x, int tile_y) {
  for (Enemigo &enemigo : lista_enemigos) {
    SpritesEnemigo *sprites = sprites_de(enemigo.tipo);
    if (sprites == nullptr || !enemigo.vivo || enemigo.tile_x != tile_x ||
        enemigo.tile_y != tile_y) {
      continue;
    }
    enemigo.animacion.recibir_golpe(sprites->duracion_golpe());
  }
}

void Caverna::golpearon_a(int tile_x, int tile_y) {
  for (Enemigo &enemigo : lista_enemigos) {
    SpritesEnemigo *sprites = sprites_de(enemigo.tipo);
    int distancia =
        std::abs(enemigo.tile_x - tile_x) + std::abs(enemigo.tile_y - tile_y);
    if (sprites == nullptr || !enemigo.vivo ||
        distancia != CAVERNA_ENEMIGO_DISTANCIA_ATAQUE ||
        enemigo.animacion.esta_atacando()) {
      continue;
    }
    // Se da vuelta para mirar al jugador
    enemigo.animacion.atacar(tile_x - enemigo.tile_x,
                             sprites->duracion_ataque());
  }
}

void Caverna::animar(long vueltas_pasadas) {
  vueltas += vueltas_pasadas;
  for (Enemigo &enemigo : lista_enemigos) {
    enemigo.animacion.animar(vueltas_pasadas);
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
  // Esqueleto, orco y vampiros: sus hojas se dibujan solas
  SpritesEnemigo *sprites = sprites_de(enemigo.tipo);
  if (sprites != nullptr) {
    SDL2pp::Color tinte = COLOR_TINTE_NEUTRO;
    if (enemigo.tipo == VAMPIRA) {
      tinte = SDL2pp::Color(255, 170, 200);
    }
    sprites->dibujar(renderer, enemigo.animacion, enemigo.vivo, vueltas,
                     enemigo.tile_x, enemigo.tile_y, camara_x, camara_y, lado,
                     tinte);
    return;
  }

  // Calaveras y trampas
  if (!enemigo.vivo)
    return;

  SDL2pp::Texture *textura = &pinches;
  FormatoEnemigo formato = FORMATO_TRAMPA;
  switch (enemigo.tipo) {
  case CALAVERA_AZUL:
    textura = &calavera_azul_quieto;
    formato = FORMATO_CALAVERA;
    break;
  case CALAVERA_VERDE:
    textura = &calavera_verde_quieto;
    formato = FORMATO_CALAVERA;
    break;
  case TRAMPA_PINCHES:
    textura = &pinches;
    formato = FORMATO_TRAMPA;
    break;
  case TRAMPA_LANZALLAMAS:
    textura = enemigo.direction == DirectionDto::Up ||
                      enemigo.direction == DirectionDto::Left
                  ? &lanzallamas_1
                  : &lanzallamas_2;
    formato = FORMATO_TRAMPA;
    break;
  default:
    return;
  }

  int cuadros = textura->GetWidth() / formato.lado;
  if (cuadros <= 0)
    return;

  int cuadro =
      static_cast<int>((vueltas / VUELTAS_POR_CUADRO_ENEMIGO) % cuadros);
  Rect origen(cuadro * formato.lado, 0, formato.lado, formato.lado);

  int tamanio = formato.lado * lado / PIXELES_POR_TILE;
  int x = enemigo.tile_x * lado + lado / 2 - tamanio / 2 - camara_x;
  int y = enemigo.tile_y * lado + lado - formato.pie * lado / PIXELES_POR_TILE -
          camara_y;

  renderer.Copy(*textura, origen, Rect(x, y, tamanio, tamanio));
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
