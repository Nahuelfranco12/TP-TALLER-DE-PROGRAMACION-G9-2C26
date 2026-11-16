#include "personaje.h"

#include <SDL2/SDL.h>
#include <algorithm>

#include "constantes_sdl.h"

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;

namespace {
const Uint8 COLORES[][3] = PALETA_ROPA;
const int PASOS_ANIMACION[] = SPRITE_PERSONAJE_PASOS;
const int FILAS_PICAR[] = SPRITE_PERSONAJE_FILAS_PICAR;
} // namespace

// Carga las texturas y deja la ropa y la posición iniciales
Personaje::Personaje(SDL2pp::Renderer &renderer)
    : cuerpo(renderer, RUTA_PERSONAJE_CUERPO),
      pantalones(renderer, RUTA_PERSONAJE_PANTALONES),
      remeras(renderer, RUTA_PERSONAJE_REMERAS),
      pelos(renderer, RUTA_PERSONAJE_PELOS),
      sombreros(renderer, RUTA_PERSONAJE_SOMBREROS),
      pantalon(PERSONAJE_PANTALON_INICIAL), remera(PERSONAJE_REMERA_INICIAL),
      pelo(PERSONAJE_PELO_INICIAL), sombrero(PERSONAJE_SOMBRERO_INICIAL),
      color_pantalon(PERSONAJE_COLOR_PANTALON_INICIAL),
      color_pelo(PERSONAJE_COLOR_PELO_INICIAL), tile_x(0), tile_y(0),
      mirando(ABAJO), vueltas_caminando(0), vueltas_restantes_paso(0),
      vueltas_picando(0), en_la_mano(ToolTypeDto::PICKAXE),
      vida(BARRA_VALOR_MAXIMO), energia(BARRA_VALOR_MAXIMO) {
  // Colores iniciales
  pantalones.SetColorMod(COLORES[color_pantalon][0], COLORES[color_pantalon][1],
                         COLORES[color_pantalon][2]);
  pelos.SetColorMod(COLORES[color_pelo][0], COLORES[color_pelo][1],
                    COLORES[color_pelo][2]);

  herramientas.emplace_back(renderer, RUTA_ESPADA);
  herramientas.emplace_back(renderer, RUTA_PICO);
  herramientas.emplace_back(renderer, RUTA_PALA);
  herramientas.emplace_back(renderer, RUTA_REGADERA);
}

// void Personaje::cambiar_color_pantalon() {
//   color_pantalon = (color_pantalon + 1) % PALETA_ROPA_CANTIDAD;
//   pantalones.SetColorMod(COLORES[color_pantalon][0], COLORES[color_pantalon][1],
//                          COLORES[color_pantalon][2]);
// }
//
// void Personaje::cambiar_color_pelo() {
//   color_pelo = (color_pelo + 1) % PALETA_ROPA_CANTIDAD;
//   pelos.SetColorMod(COLORES[color_pelo][0], COLORES[color_pelo][1],
//                     COLORES[color_pelo][2]);
// }

void Personaje::vestir(int nuevo_sombrero, int nuevo_pelo, int nuevo_pantalon,
                       int nueva_remera) {
  sombrero = nuevo_sombrero;
  pelo = nuevo_pelo;
  pantalon = nuevo_pantalon;
  remera = nueva_remera;
}

bool Personaje::aplicar(int nuevo_x, int nuevo_y) {
  if (nuevo_x == tile_x && nuevo_y == tile_y) {
    return false;
  }

  if (nuevo_x > tile_x) {
    mirando = DERECHA;
  } else if (nuevo_x < tile_x) {
    mirando = IZQUIERDA;
  } else if (nuevo_y > tile_y) {
    mirando = ABAJO;
  } else if (nuevo_y < tile_y) {
    mirando = ARRIBA;
  }

  tile_x = nuevo_x;
  tile_y = nuevo_y;
  vueltas_restantes_paso = PERSONAJE_VUELTAS_POR_PASO;
  return true;
}

void Personaje::animar(long vueltas) {
  if (vueltas_restantes_paso > 0) {
    vueltas_caminando += vueltas;
    vueltas_restantes_paso -= vueltas;
  } else {
    vueltas_caminando = 0;
  }
  if (vueltas_picando > 0) {
    vueltas_picando -= vueltas;
  }
}

void Personaje::mirar(Direccion direccion) { mirando = direccion; }

void Personaje::picar() {
  if (vueltas_picando <= 0) {
    vueltas_picando = PERSONAJE_DURACION_PICAR;
  }
}

void Personaje::agarrar(ToolTypeDto herramienta) { en_la_mano = herramienta; }

void Personaje::poner_vida(double nueva_vida) { vida = nueva_vida; }

void Personaje::poner_energia(double nueva_energia) { energia = nueva_energia; }

double Personaje::obtener_vida() const { return vida; }

int Personaje::obtener_tile_x() const { return tile_x; }

Direccion Personaje::obtener_direccion() const { return mirando; }

int Personaje::obtener_tile_y() const { return tile_y; }

void Personaje::dibujar(Renderer &renderer, int camara_x, int camara_y) {
  int columna = 0;
  if (vueltas_restantes_paso > 0) {
    long paso = (vueltas_caminando / PERSONAJE_VUELTAS_POR_CUADRO) %
                PERSONAJE_CUADROS_CAMINAR;
    columna = PASOS_ANIMACION[paso];
  }

  int rebote = 0;
  if (columna != 0) {
    rebote = PERSONAJE_REBOTE;
  }

  int fila_cuerpo = mirando;
  if (mirando == IZQUIERDA) {
    fila_cuerpo = DERECHA;
  }
  if (vueltas_picando > 0) {
    long transcurrido = PERSONAJE_DURACION_PICAR - vueltas_picando;
    columna =
        static_cast<int>(transcurrido / PERSONAJE_VUELTAS_POR_CUADRO_PICAR);
    if (columna >= PERSONAJE_CUADROS_PICAR) {
      columna = PERSONAJE_CUADROS_PICAR - 1;
    }
    fila_cuerpo = FILAS_PICAR[fila_cuerpo];
    rebote = 0;
  }
  int x = tile_x * TAMANIO_TILE - camara_x;
  int y = tile_y * TAMANIO_TILE - TAMANIO_TILE - camara_y;
  dibujar_capas(renderer, x, y, TAMANIO_TILE, columna, fila_cuerpo, mirando,
                rebote);
  dibujar_herramienta(renderer, x, y, TAMANIO_TILE);

  int barra_x = x + TAMANIO_TILE / 2 - BARRA_ANCHO / 2;
  int barra_energia_y = y - BARRA_ALTO - BARRA_SEPARACION;
  int barra_vida_y = barra_energia_y - BARRA_ALTO - BARRA_SEPARACION;
  const SDL2pp::Color color_vida = COLOR_BARRA_VIDA;
  const SDL2pp::Color color_energia = COLOR_BARRA_ENERGIA;
  dibujar_barra(renderer, barra_x, barra_vida_y, vida, color_vida);
  dibujar_barra(renderer, barra_x, barra_energia_y, energia, color_energia);
}

// void Personaje::dibujar_quieto(Renderer &renderer, int otro_tile_x,
//                                int otro_tile_y, int camara_x, int camara_y,
//                                int lado) {
//   int x = otro_tile_x * lado - camara_x;
//   int y = otro_tile_y * lado - lado - camara_y;
//   dibujar_capas(renderer, x, y, lado, 0, ABAJO, ABAJO, 0);
// }

void Personaje::dibujar_icono(Renderer &renderer, int centro_x, int pie_y,
                              int lado) {
  int fila_cuerpo = mirando;
  if (mirando == IZQUIERDA) {
    fila_cuerpo = DERECHA;
  }
  int arriba_y = pie_y - SPRITE_PERSONAJE_ALTO * lado / TAMANIO_TILE_ASSET;
  dibujar_capas(renderer, centro_x - lado / 2, arriba_y, lado, 0, fila_cuerpo,
                mirando, 0);
}

void Personaje::dibujar_capas(Renderer &renderer, int x, int y, int lado,
                              int columna, int fila_cuerpo, Direccion direccion,
                              int rebote) {
  int fila = direccion;
  int flip = SDL_FLIP_NONE;
  if (direccion == IZQUIERDA) {
    fila = DERECHA;
    flip = SDL_FLIP_HORIZONTAL;
  }

  int ancho = SPRITE_PERSONAJE_ANCHO * lado / TAMANIO_TILE_ASSET;
  int alto = SPRITE_PERSONAJE_ALTO * lado / TAMANIO_TILE_ASSET;
  Rect destino(x, y, ancho, alto);
  int desplazamiento = rebote * lado / TAMANIO_TILE_ASSET;

  // Cuerpo
  Rect origen_cuerpo(columna * SPRITE_PERSONAJE_ANCHO,
                     fila_cuerpo * SPRITE_PERSONAJE_ALTO,
                     SPRITE_PERSONAJE_ANCHO, SPRITE_PERSONAJE_ALTO);
  renderer.Copy(cuerpo, origen_cuerpo, destino, 0.0, NullOpt, flip);

  // Pantalones
  int pantalon_x =
      (pantalon % SPRITE_PANTALONES_POR_FILA) * SPRITE_PANTALONES_ANCHO_BLOQUE +
      columna * SPRITE_PERSONAJE_ANCHO;
  int pantalon_y =
      (pantalon / SPRITE_PANTALONES_POR_FILA) * SPRITE_PANTALONES_ALTO_BLOQUE +
      fila_cuerpo * SPRITE_PERSONAJE_ALTO;
  Rect origen_pantalon(pantalon_x, pantalon_y, SPRITE_PERSONAJE_ANCHO,
                       SPRITE_PERSONAJE_ALTO);
  renderer.Copy(pantalones, origen_pantalon, destino, 0.0, NullOpt, flip);

  // Remera
  int fila_remera = SPRITE_REMERA_FILA_ABAJO;
  if (direccion == DERECHA) {
    fila_remera = SPRITE_REMERA_FILA_DERECHA;
  } else if (direccion == IZQUIERDA) {
    fila_remera = SPRITE_REMERA_FILA_IZQUIERDA;
  } else if (direccion == ARRIBA) {
    fila_remera = SPRITE_REMERA_FILA_ARRIBA;
  }
  int remera_x = (remera % SPRITE_REMERAS_POR_FILA) * SPRITE_REMERA_LADO;
  int remera_y =
      (remera / SPRITE_REMERAS_POR_FILA) * SPRITE_REMERA_ALTO_BLOQUE +
      fila_remera;
  Rect origen_remera(remera_x, remera_y, SPRITE_REMERA_LADO,
                     SPRITE_REMERA_LADO);
  int lado_remera = SPRITE_REMERA_LADO * lado / TAMANIO_TILE_ASSET;
  Rect destino_remera(x + SPRITE_REMERA_X * lado / TAMANIO_TILE_ASSET,
                      y + SPRITE_REMERA_Y * lado / TAMANIO_TILE_ASSET +
                          desplazamiento,
                      lado_remera, lado_remera);
  renderer.Copy(remeras, origen_remera, destino_remera);

  // Brazos
  Rect origen_brazos(SPRITE_BRAZOS_X + columna * SPRITE_PERSONAJE_ANCHO,
                     fila_cuerpo * SPRITE_PERSONAJE_ALTO,
                     SPRITE_PERSONAJE_ANCHO, SPRITE_PERSONAJE_ALTO);
  renderer.Copy(cuerpo, origen_brazos, destino, 0.0, NullOpt, flip);

  // Pelo
  int pelo_x = (pelo % SPRITE_PELOS_POR_FILA) * SPRITE_PERSONAJE_ANCHO;
  int pelo_y = (pelo / SPRITE_PELOS_POR_FILA) * SPRITE_PELO_ALTO_BLOQUE +
               fila * SPRITE_PERSONAJE_ALTO;
  Rect origen_pelo(pelo_x, pelo_y, SPRITE_PERSONAJE_ANCHO,
                   SPRITE_PERSONAJE_ALTO);
  Rect destino_pelo(x, y + desplazamiento, ancho, alto);
  renderer.Copy(pelos, origen_pelo, destino_pelo, 0.0, NullOpt, flip);

  // Sombrero
  if (sombrero >= 0) {
    int fila_sombrero = SPRITE_SOMBRERO_FILA_ABAJO;
    if (direccion == DERECHA) {
      fila_sombrero = SPRITE_SOMBRERO_FILA_DERECHA;
    } else if (direccion == IZQUIERDA) {
      fila_sombrero = SPRITE_SOMBRERO_FILA_IZQUIERDA;
    } else if (direccion == ARRIBA) {
      fila_sombrero = SPRITE_SOMBRERO_FILA_ARRIBA;
    }
    int sombrero_x =
        (sombrero % SPRITE_SOMBREROS_POR_FILA) * SPRITE_SOMBRERO_LADO;
    int sombrero_y =
        (sombrero / SPRITE_SOMBREROS_POR_FILA) * SPRITE_SOMBRERO_ALTO_BLOQUE +
        fila_sombrero;
    Rect origen_sombrero(sombrero_x, sombrero_y, SPRITE_SOMBRERO_LADO,
                         SPRITE_SOMBRERO_LADO);
    int lado_sombrero = SPRITE_SOMBRERO_LADO * lado / TAMANIO_TILE_ASSET;
    Rect destino_sombrero(x + SPRITE_SOMBRERO_X * lado / TAMANIO_TILE_ASSET,
                          y + SPRITE_SOMBRERO_Y * lado / TAMANIO_TILE_ASSET +
                              desplazamiento,
                          lado_sombrero, lado_sombrero);
    renderer.Copy(sombreros, origen_sombrero, destino_sombrero);
  }
}

void Personaje::dibujar_herramienta(Renderer &renderer, int x, int y,
                                    int lado) {
  if (mirando == ARRIBA) {
    return;
  }

  Texture &icono = herramientas[static_cast<int>(en_la_mano)];
  int ancho = icono.GetWidth() * lado / ICONO_PIXELES_POR_TILE;
  int alto = icono.GetHeight() * lado / ICONO_PIXELES_POR_TILE;

  // Mano derecha
  int mano_x = x + SPRITE_MANO_DERECHA_X * lado / TAMANIO_TILE_ASSET;
  int mano_y = y + SPRITE_MANO_Y * lado / TAMANIO_TILE_ASSET;
  int flip = SDL_FLIP_NONE;
  if (mirando == IZQUIERDA) {
    mano_x = x + SPRITE_MANO_IZQUIERDA_X * lado / TAMANIO_TILE_ASSET - ancho;
    flip = SDL_FLIP_HORIZONTAL;
  }

  renderer.Copy(icono, NullOpt, Rect(mano_x, mano_y, ancho, alto), 0.0, NullOpt,
                flip);
}

void Personaje::dibujar_barra(Renderer &renderer, int barra_x, int barra_y,
                              double valor, const SDL2pp::Color &color) const {
  int lleno = static_cast<int>(BARRA_ANCHO * valor / BARRA_VALOR_MAXIMO);
  lleno = std::clamp(lleno, 0, BARRA_ANCHO);

  // Borde negro
  const SDL2pp::Color borde = COLOR_BARRA_BORDE;
  renderer.SetDrawColor(borde);
  renderer.FillRect(Rect(barra_x - BARRA_BORDE, barra_y - BARRA_BORDE,
                         BARRA_ANCHO + 2 * BARRA_BORDE,
                         BARRA_ALTO + 2 * BARRA_BORDE));

  // Fondo gris
  const SDL2pp::Color fondo = COLOR_BARRA_FONDO;
  renderer.SetDrawColor(fondo);
  renderer.FillRect(Rect(barra_x, barra_y, BARRA_ANCHO, BARRA_ALTO));

  // Lo que queda de vida
  if (lleno > 0) {
    renderer.SetDrawColor(color);
    renderer.FillRect(Rect(barra_x, barra_y, lleno, BARRA_ALTO));
  }
}
