#include "ventana_cofre.h"

#include "constantes_sdl.h"

using SDL2pp::Rect;
using SDL2pp::Renderer;

Rect VentanaCofre::rect_casillero(int i, int ancho_ventana, int alto_ventana) {
  int fila = i / COFRE_COLUMNAS;
  int columna = i % COFRE_COLUMNAS;

  int ancho = COFRE_COLUMNAS * INVENTARIO_LADO_CASILLERO;
  int x = (ancho_ventana - ancho) / 2 + columna * INVENTARIO_LADO_CASILLERO;
  int abajo = alto_ventana - INVENTARIO_LADO_CASILLERO - INVENTARIO_MARGEN_ABAJO - COFRE_SEPARACION;
  int y = abajo - (COFRE_FILAS - fila) * INVENTARIO_LADO_CASILLERO;
  return Rect(x, y, INVENTARIO_LADO_CASILLERO, INVENTARIO_LADO_CASILLERO);
}

void VentanaCofre::actualizar(
    const std::map<GamePositionDto, EntityDto> &entidades) {
  abierta = false;
  casilleros.clear();
  for (const auto &[posicion, entidad] : entidades) {
    if (entidad.type == EntityTypeDto::CHEST && entidad.chest.openedByMe) {
      abierta = true;
      casilleros.assign(entidad.chest.slots.begin(), entidad.chest.slots.end());
    }
  }
}

bool VentanaCofre::click(int x, int y, int ancho_ventana, int alto_ventana, int &indice) const {
  if (!abierta)
    return false;
  for (int i = 0; i < COFRE_CASILLEROS; i++) {
    if (rect_casillero(i, ancho_ventana, alto_ventana).Contains(x, y)) {
      indice = i;
      return true;
    }
  }
  return false;
}

void VentanaCofre::dibujar(Renderer &renderer, Inventario &inventario, int ancho_ventana, int alto_ventana) const {
  if (!abierta)
    return;

  const SDL2pp::Color fondo = COLOR_CASILLERO;
  const SDL2pp::Color borde = COLOR_CASILLERO_BORDE;
  for (int i = 0; i < COFRE_CASILLEROS; i++) {
    Rect lugar = rect_casillero(i, ancho_ventana, alto_ventana);
    renderer.SetDrawColor(fondo);
    renderer.FillRect(lugar);
    if (i < static_cast<int>(casilleros.size()))
      inventario.dibujar_regalo(renderer, casilleros[i], lugar);
    renderer.SetDrawColor(borde);
    renderer.DrawRect(lugar);
  }
}