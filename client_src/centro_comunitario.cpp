#include "centro_comunitario.h"
#include "inventario.h"

#include <algorithm>

#include <SDL2/SDL.h>

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;

namespace {
const SDL_Rect MODELOS_SETS[] = SPRITE_MODELOS_SETS;
const SDL_Rect FONDO = SPRITE_FONDO_CENTRO;

const SDL2pp::Color BLANCO = COLOR_TEXTO;
const SDL2pp::Color MARRON = COLOR_TEXTO_CENTRO;

const char *TITULOS[] = TITULOS_SETS;

struct Requisito {
    const char *nombre;
    ItemTypeDto item;
    int cantidad;
    bool calidad_alta;
};

const Requisito REQUISITOS_CULTIVOS[] = {
    {"Frutilla increíble o perfecta", ItemTypeDto::CROP_STRAWBERRY, 3, true},
    {"Cebolla de verdeo increíble o perfecta", ItemTypeDto::CROP_GREEN_ONION, 3, true},
    {"Papa increíble o perfecta", ItemTypeDto::CROP_POTATO, 3, true},
    {"Calabaza increíble o perfecta", ItemTypeDto::CROP_PUMPKIN, 3, true},
};

const Requisito REQUISITOS_METALES[] = {
    {"Carbón", ItemTypeDto::MINERAL_COAL, 10, false},
    {"Lapislázuli", ItemTypeDto::MINERAL_LAPIZLAZULI, 7, false},
    {"Hierro", ItemTypeDto::MINERAL_IRON, 5, false},
    {"Oro", ItemTypeDto::MINERAL_GOLD, 3, false},
};

const Requisito REQUISITOS_ANIMALES[] = {
    {"Leche", ItemTypeDto::COW_MILK, 5, false}, 
    {"Huevos", ItemTypeDto::CHICKEN_EGG, 10, false},
};

const char *LINEAS_PELEA[] = {
    "3 esqueletos de habitaciones seguidas", "2 vampiros de la misma pareja", 
    "4 orcos del mismo grupo", "1 calavera sin recibir daño"
};

int tile_de_pixel(int pixel) {
    int tile = pixel / TAMANIO_TILE;
    if (pixel < 0 && pixel % TAMANIO_TILE != 0) {
        tile--;
    }
    return tile;
}

// Ejemplo: Carbón: 4 / 10
std::string renglon(const Requisito &requisito, const Inventario &inventario) {
    int tengo = inventario.contar(requisito.item, requisito.calidad_alta);
    return std::string(requisito.nombre) + ": " + std::to_string(tengo) + " / " + std::to_string(requisito.cantidad);
}
}

CentroComunitario::CentroComunitario(Renderer &renderer) 
      : ofrendas(renderer, RUTA_OFRENDAS_CENTRO_COMUNITARIO),
      fuente(RUTA_FUENTE_JUEGO, CENTRO_TAMANIO_LETRA),
      fuente_chica(RUTA_FUENTE_JUEGO, CENTRO_TAMANIO_LETRA_CHICA),
      texto_canjear(renderer, fuente.RenderUTF8_Blended(TEXTO_JUEGO_CANJEAR, BLANCO)),
      texto_salir(renderer, fuente.RenderUTF8_Blended(TEXTO_JUEGO_SALIR, BLANCO)),
      set_abierto(SET_CERRADO) {

    for (const char *titulo : TITULOS) {
        // cppcheck-suppress useStlAlgorithm
        titulos.emplace_back(renderer, fuente.RenderUTF8_Blended(titulo, MARRON));
    }

    // cppcheck-suppress useInitializationList
    lista_sets = CENTRO_SETS;
}

void CentroComunitario::dibujar_figurin(Renderer &renderer, const Set &set, int camara_x, int camara_y, int lado) {
    const SDL_Rect &modelo = MODELOS_SETS[set.modelo];
    Rect origen(modelo.x, modelo.y, modelo.w, modelo.h);
    
    int tamanio = modelo.w * lado / TAMANIO_TILE_ASSET;
    int x = set.tile_x * lado - camara_x;
    int y = (set.tile_y + 1) * lado - tamanio - camara_y;
    renderer.Copy(ofrendas, origen, Rect(x, y, tamanio, tamanio));
}

void CentroComunitario::dibujar(Renderer &renderer, int camara_x, int camara_y, int lado) {
    for (const Set &set : lista_sets) {
        dibujar_figurin(renderer, set, camara_x, camara_y, lado);
    }
}

CentroComunitario::AccionCentro
CentroComunitario::click_set(int x, int y, int camara_x, int camara_y) {
    if (set_abierto != SET_CERRADO) {
        if (boton_salir.Contains(x, y)) {
            cerrar_set();
            return SALIR;
        }
        if (boton_canjear.Contains(x, y)) {
            return CANJEAR;
        }
        return NINGUNA;
    }

    // Qué tile toqué
    int tile_x = tile_de_pixel(x + camara_x);
    int tile_y = tile_de_pixel(y + camara_y);

    for (const Set &set : lista_sets) {
        bool en_x = tile_x == set.tile_x || tile_x == set.tile_x + 1;
        bool en_y = tile_y == set.tile_y || tile_y == set.tile_y - 1;
        if (en_x && en_y) {
            set_abierto = set.modelo;
            return CONSULTAR;
        }
    }
    return NINGUNA;
}

bool CentroComunitario::hay_set_abierto() const {
    return set_abierto != SET_CERRADO;
}

void CentroComunitario::cerrar_set() {
    set_abierto = SET_CERRADO;
}

// La caja de un set
std::vector<std::string>
CentroComunitario::armar_lineas(const Inventario &inventario,
                                size_t monedas) const {
  std::vector<std::string> resultado;
  switch (set_abierto) {
  case SET_CULTIVOS:
    for (const Requisito &requisito : REQUISITOS_CULTIVOS) {
      // cppcheck-suppress useStlAlgorithm
      resultado.push_back(renglon(requisito, inventario));
    }
    break;
  case SET_METALES:
    for (const Requisito &requisito : REQUISITOS_METALES) {
      // cppcheck-suppress useStlAlgorithm
      resultado.push_back(renglon(requisito, inventario));
    }
    break;
  case SET_ANIMALES:
    for (const Requisito &requisito : REQUISITOS_ANIMALES) {
      // cppcheck-suppress useStlAlgorithm
      resultado.push_back(renglon(requisito, inventario));
    }
    break;
  case SET_PELEA:
    for (const char *linea : LINEAS_PELEA) {
      // cppcheck-suppress useStlAlgorithm
      resultado.push_back(linea);
    }
    break;
  case SET_DINERO:
    resultado.push_back(TEXTO_JUEGO_MONEDAS + std::to_string(monedas) + " / " +
                        std::to_string(CENTRO_MONEDAS_SET));
    break;
  default:
    break;
  }
  return resultado;
}

void CentroComunitario::actualizar_lineas(Renderer &renderer,
                                          const Inventario &inventario,
                                          size_t monedas) {
  std::vector<std::string> nuevas = armar_lineas(inventario, monedas);
  if (nuevas == lineas) {
    return;
  }
  lineas = nuevas;
  textura_lineas.clear();
  for (const std::string &linea : lineas) {
    // cppcheck-suppress useStlAlgorithm
    textura_lineas.emplace_back(renderer,
                                 fuente_chica.RenderUTF8_Blended(linea, MARRON));
  }
}

void CentroComunitario::dibujar_boton(Renderer &renderer, const Rect &boton,
                                      Texture &texto) {
  const SDL2pp::Color fondo_boton = COLOR_BOTON_FONDO;
  const SDL2pp::Color borde_boton = COLOR_BOTON_BORDE;
  renderer.SetDrawColor(fondo_boton);
  renderer.FillRect(boton);
  renderer.SetDrawColor(borde_boton);
  renderer.DrawRect(boton);
  renderer.Copy(texto, NullOpt,
                Rect(boton.x + (boton.w - texto.GetWidth()) / 2,
                     boton.y + (boton.h - texto.GetHeight()) / 2,
                     texto.GetWidth(), texto.GetHeight()));
}

void CentroComunitario::dibujar_set(Renderer &renderer,
                                    const Inventario &inventario,
                                    size_t monedas) {
  if (set_abierto == SET_CERRADO) {
    return;
  }
  int ancho_ventana = renderer.GetOutputWidth();
  int alto_ventana = renderer.GetOutputHeight();

  // Fondo oscuro
  const SDL2pp::Color oscurecer = COLOR_TIENDA_OSCURECER;
  renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
  renderer.SetDrawColor(oscurecer);
  renderer.FillRect(Rect(0, 0, ancho_ventana, alto_ventana));

  // Pared
  double escala_ancho = (ancho_ventana - CENTRO_MARGEN_ANCHO) / double(FONDO.w);
  double escala_alto = (alto_ventana - CENTRO_MARGEN_ALTO) / double(FONDO.h);
  double escala = std::min(escala_ancho, escala_alto);
  int ancho = static_cast<int>(FONDO.w * escala);
  int alto = static_cast<int>(FONDO.h * escala);
  Rect panel((ancho_ventana - ancho) / 2, (alto_ventana - alto) / 2, ancho, alto);
  renderer.Copy(ofrendas, Rect(FONDO.x, FONDO.y, FONDO.w, FONDO.h), panel);

  // Nombre del set
  int y = panel.y + panel.h / 8;
  Texture &titulo = titulos[set_abierto];
  renderer.Copy(titulo, NullOpt,
                Rect((ancho_ventana - titulo.GetWidth()) / 2, y,
                     titulo.GetWidth(), titulo.GetHeight()));
  y += titulo.GetHeight() + CENTRO_SEPARACION_LINEAS;

  // El figurín grande
  const SDL_Rect &modelo = MODELOS_SETS[set_abierto];
  renderer.Copy(ofrendas, Rect(modelo.x, modelo.y, modelo.w, modelo.h),
                Rect((ancho_ventana - CENTRO_LADO_FIGURIN_CAJA) / 2, y,
                     CENTRO_LADO_FIGURIN_CAJA, CENTRO_LADO_FIGURIN_CAJA));
  y += CENTRO_LADO_FIGURIN_CAJA + CENTRO_SEPARACION_LINEAS;

  // Lo que pide y cuánto tengo
  actualizar_lineas(renderer, inventario, monedas);
  for (Texture &linea : textura_lineas) {
    renderer.Copy(linea, NullOpt,
                  Rect((ancho_ventana - linea.GetWidth()) / 2, y,
                       linea.GetWidth(), linea.GetHeight()));
    y += linea.GetHeight() + CENTRO_SEPARACION_LINEAS;
  }

  // Botones Canjear y Salir, abajo del panel
  int ancho_canjear = texto_canjear.GetWidth() + 2 * TIENDA_RELLENO_BOTON;
  int ancho_salir = texto_salir.GetWidth() + 2 * TIENDA_RELLENO_BOTON;
  int x = (ancho_ventana - ancho_canjear - TIENDA_SEPARACION_BOTONES - ancho_salir) / 2;
  int y_botones = panel.y + panel.h + CENTRO_MARGEN_BOTONES;
  boton_canjear = Rect(x, y_botones, ancho_canjear, TIENDA_ALTO_BOTON);
  boton_salir = Rect(x + ancho_canjear + TIENDA_SEPARACION_BOTONES, y_botones,
                     ancho_salir, TIENDA_ALTO_BOTON);
  dibujar_boton(renderer, boton_canjear, texto_canjear);
  dibujar_boton(renderer, boton_salir, texto_salir);
}