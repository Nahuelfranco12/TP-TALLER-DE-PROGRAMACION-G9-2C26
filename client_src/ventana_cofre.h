#ifndef VENTANA_COFRE_H
#define VENTANA_COFRE_H

#include <map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/game_dtos.h"
#include "inventario.h"

class VentanaCofre {
private:
  bool abierta = false;
  std::vector<InventorySlotDto> casilleros;

  static SDL2pp::Rect rect_casillero(int i, int ancho_ventana,
                                     int alto_ventana);

public:
  
  void actualizar(const std::map<GamePositionDto, EntityDto> &entidades);

  bool esta_abierta() const { return abierta; }

  /*
  * Si está abierta la ventana, devuelve en "indice" el casillero clickeado del cofre.
  */
  bool click(int x, int y, int ancho_ventana, int alto_ventana, int &indice) const;

  void dibujar(SDL2pp::Renderer &renderer, Inventario &inventario, int ancho_ventana, int alto_ventana) const;
};

#endif