#include "personaje.h"

#include <SDL2/SDL.h>
#include <algorithm>

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;

namespace {

// Paleta de colores
const Uint8 COLORES[8][3] = {
    {60, 90, 200},   // azul
    {150, 80, 30},   // marrón
    {40, 30, 20},    // negro
    {230, 190, 90},  // rubio
    {200, 60, 40},   // rojo
    {70, 150, 70},   // verde
    {230, 230, 230}, // blanco
    {150, 80, 200},  // violeta
};
const int CANTIDAD_COLORES = 8;

const int ESCALA = 4;
const int TILE = 16 * ESCALA;

const long VUELTAS_POR_PASO = 16;

// Animación
const int PASOS_ANIMACION[4] = {0, 1, 0, 2}; // columnas
const long VUELTAS_POR_CUADRO = 9;           // 9 x 16 ms = 0.15

// Vida y energía
const double VALOR_MAXIMO = 100.0;
const int ANCHO_BARRA = 48;
const int ALTO_BARRA = 6;
const SDL2pp::Color AMARILLO = {240, 200, 40, 255};
const SDL2pp::Color VERDE = {70, 190, 70, 255};

const int CUADROS_PICAR = 5;
const long VUELTAS_POR_CUADRO_PICAR = 5;
const long DURACION_PICAR = CUADROS_PICAR * VUELTAS_POR_CUADRO_PICAR;
const int FILAS_PICAR[3] = {11, 8, 6};
} // namespace

// Carga las texturas y deja la ropa y la posición iniciales
Personaje::Personaje(SDL2pp::Renderer &renderer)
    : cuerpo(renderer,
             "assets/personaje/StardewValley_Character_Farmer Base.png"),
      pantalones(renderer,
                 "assets/personaje/StardewValley_Character_Pants.png"),
      remeras(renderer, "assets/personaje/StardewValley_Character_Shirts.png"),
      pelos(renderer,
            "assets/personaje/StardewValley_Character_Hairstyles.png"),
      sombreros(renderer, "assets/personaje/StardewValley_Character_Hats.png"),
      pantalon(0), remera(5), pelo(3), sombrero(2), color_pantalon(0),
      color_pelo(1), tile_x(0), tile_y(0), mirando(ABAJO), vueltas_caminando(0),
      vueltas_restantes_paso(0), vueltas_picando(0), en_la_mano(ToolTypeDto::PICKAXE), vida(VALOR_MAXIMO), energia(VALOR_MAXIMO) {
  // Colores iniciales
  pantalones.SetColorMod(COLORES[color_pantalon][0], COLORES[color_pantalon][1],
                         COLORES[color_pantalon][2]);
  pelos.SetColorMod(COLORES[color_pelo][0], COLORES[color_pelo][1],
                    COLORES[color_pelo][2]);

  herramientas.emplace_back(renderer, "assets/inventario/sword.png");
  herramientas.emplace_back(renderer, "assets/inventario/pickaxe.png");
  herramientas.emplace_back(renderer, "assets/inventario/shovel.png");
  herramientas.emplace_back(renderer, "assets/inventario/basket.png");
}

void Personaje::cambiar_color_pantalon() {
  color_pantalon = (color_pantalon + 1) % CANTIDAD_COLORES;
  pantalones.SetColorMod(COLORES[color_pantalon][0], COLORES[color_pantalon][1],
                         COLORES[color_pantalon][2]);
}

void Personaje::cambiar_color_pelo() {
  color_pelo = (color_pelo + 1) % CANTIDAD_COLORES;
  pelos.SetColorMod(COLORES[color_pelo][0], COLORES[color_pelo][1],
                    COLORES[color_pelo][2]);
}

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
  vueltas_restantes_paso = VUELTAS_POR_PASO;
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

void Personaje::mirar(Direccion direccion) {
  mirando = direccion;
}

void Personaje::picar() {
  if (vueltas_picando <= 0) {
    vueltas_picando = DURACION_PICAR;
  }
}

void Personaje::agarrar(ToolTypeDto herramienta) {
  en_la_mano = herramienta;
}

void Personaje::poner_vida(double nueva_vida) {
  vida = nueva_vida;
}

void Personaje::poner_energia(double nueva_energia) {
  energia = nueva_energia;
}

int Personaje::obtener_tile_x() const { return tile_x; }

Direccion Personaje::obtener_direccion() const { return mirando; }

int Personaje::obtener_tile_y() const { return tile_y; }

void Personaje::dibujar(Renderer &renderer, int camara_x, int camara_y) {
  int columna = 0;
  if (vueltas_restantes_paso > 0) {
    long paso = (vueltas_caminando / VUELTAS_POR_CUADRO) % 4;
    columna = PASOS_ANIMACION[paso];
  }

  int rebote = 0;
  if (columna != 0) {
    rebote = 1;
  }

  int fila_cuerpo = mirando;
  if (mirando == IZQUIERDA) {
    fila_cuerpo = DERECHA;
  }
  if (vueltas_picando > 0) {
    long transcurrido = DURACION_PICAR - vueltas_picando;
    columna = static_cast<int>(transcurrido / VUELTAS_POR_CUADRO_PICAR);
    if (columna >= CUADROS_PICAR) {
      columna = CUADROS_PICAR - 1;
    }
    fila_cuerpo = FILAS_PICAR[fila_cuerpo];
    rebote = 0;
  }
  int x = tile_x * TILE - camara_x;
  int y = tile_y * TILE - TILE - camara_y;
  dibujar_capas(renderer, x, y, TILE, columna, fila_cuerpo, mirando, rebote);
  dibujar_herramienta(renderer, x, y, TILE);

  int barra_x = x + TILE / 2 - ANCHO_BARRA / 2;
  int barra_vida_y = y - 2 * ALTO_BARRA - 4;
  int barra_energia_y = y - ALTO_BARRA -2;
  dibujar_barra(renderer, barra_x, barra_vida_y, vida, AMARILLO);
  dibujar_barra(renderer, barra_x, barra_energia_y, energia, VERDE);
}

void Personaje::dibujar_quieto(Renderer &renderer, int otro_tile_x,
                               int otro_tile_y, int camara_x, int camara_y,
                               int lado) {
  int x = otro_tile_x * lado - camara_x;
  int y = otro_tile_y * lado - lado - camara_y;
  dibujar_capas(renderer, x, y, lado, 0, ABAJO, ABAJO, 0);
}

  void Personaje::dibujar_icono(Renderer &renderer, int centro_x, int pie_y, int lado) {
    int fila_cuerpo = mirando;
    if (mirando == IZQUIERDA) {
      fila_cuerpo = DERECHA;
    }
    dibujar_capas(renderer, centro_x - lado / 2, pie_y - 2 * lado, lado, 0, fila_cuerpo, mirando, 0);
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

  Rect destino(x, y, 16 * lado / 16, 32 * lado / 16);
  int desplazamiento = rebote * lado / 16;

  // Cuerpo
  Rect origen_cuerpo(columna * 16, fila_cuerpo * 32, 16, 32);
  renderer.Copy(cuerpo, origen_cuerpo, destino, 0.0, NullOpt, flip);

  // Pantalones
  Rect origen_pantalon((pantalon % 10) * 192 + columna * 16,
                       (pantalon / 10) * 688 + fila_cuerpo * 32, 16, 32);
  renderer.Copy(pantalones, origen_pantalon, destino, 0.0, NullOpt, flip);

  // Remera
  int fila_remera = 0;
  if (direccion == DERECHA) {
    fila_remera = 8;
  } else if (direccion == IZQUIERDA) {
    fila_remera = 16;
  } else if (direccion == ARRIBA) {
    fila_remera = 24;
  }
  Rect origen_remera((remera % 16) * 8, (remera / 16) * 32 + fila_remera, 8, 8);
  Rect destino_remera(x + 4 * lado / 16, y + 15 * lado / 16 + desplazamiento,
                      8 * lado / 16, 8 * lado / 16);
  renderer.Copy(remeras, origen_remera, destino_remera);

  // Brazos
  Rect origen_brazos(96 + columna * 16, fila_cuerpo * 32, 16, 32);
  renderer.Copy(cuerpo, origen_brazos, destino, 0.0, NullOpt, flip);

  // Pelo
  Rect origen_pelo((pelo % 16) * 16, (pelo / 16) * 96 + fila * 32, 16, 32);
  Rect destino_pelo(x, y + desplazamiento, 16 * lado / 16, 32 * lado / 16);
  renderer.Copy(pelos, origen_pelo, destino_pelo, 0.0, NullOpt, flip);

  // Sombrero
  if (sombrero >= 0) {
    int fila_sombrero = 0;
    if (direccion == DERECHA) {
      fila_sombrero = 20;
    } else if (direccion == IZQUIERDA) {
      fila_sombrero = 40;
    } else if (direccion == ARRIBA) {
      fila_sombrero = 60;
    }
    Rect origen_sombrero((sombrero % 12) * 20,
                         (sombrero / 12) * 80 + fila_sombrero, 20, 20);
    Rect destino_sombrero(x - 2 * lado / 16, y - 4 * lado / 16 + desplazamiento,
                          20 * lado / 16, 20 * lado / 16);
    renderer.Copy(sombreros, origen_sombrero, destino_sombrero);
  }
}

void Personaje::dibujar_herramienta(Renderer &renderer, int x, int y, int lado) {
  if (mirando ==ARRIBA) {
    return;
  }

  Texture &icono = herramientas[static_cast<int>(en_la_mano)];
  int ancho = icono.GetWidth() * lado / 24;
  int alto = icono.GetHeight() * lado / 24;

  // Mano derecha
  int mano_x = x + 9 * lado / 16;
  int mano_y = y + 16 * lado / 16;
  int flip = SDL_FLIP_NONE;
  if (mirando == IZQUIERDA) {
    mano_x = x + 7 * lado / 16 - ancho;
    flip = SDL_FLIP_HORIZONTAL;
  }

  renderer.Copy(icono, NullOpt, Rect(mano_x, mano_y, ancho, alto), 0.0, NullOpt, flip);
}

void Personaje::dibujar_barra(Renderer &renderer, int barra_x, int barra_y, double valor, const SDL2pp::Color &color) const {
  int lleno = static_cast<int>(ANCHO_BARRA * valor / VALOR_MAXIMO);
  lleno = std::clamp(lleno, 0, ANCHO_BARRA);

  // Borde negro
  renderer.SetDrawColor(0, 0, 0, 255);
  renderer.FillRect(Rect(barra_x - 1, barra_y - 1, ANCHO_BARRA + 2, ALTO_BARRA + 2));

  // Fondo gris
  renderer.SetDrawColor(70, 70, 70, 255);
  renderer.FillRect(Rect(barra_x, barra_y, ANCHO_BARRA, ALTO_BARRA));

  // Lo que queda de vida
  if (lleno > 0) {
    renderer.SetDrawColor(color);
    renderer.FillRect(Rect(barra_x, barra_y, lleno, ALTO_BARRA));
  }
}
