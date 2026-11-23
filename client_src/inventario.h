#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "common_src/game_dtos.h"

enum Herramienta { PICO, REGADERA, PALA, ESPADA };

class Inventario {
private:
  SDL2pp::Texture minerales;
  SDL2pp::Texture cultivos;
  SDL2pp::Texture huevo;
  SDL2pp::Texture leche;
  std::vector<SDL2pp::Texture> iconos_herramienta;
  SDL2pp::Font fuente;
  std::vector<SDL2pp::Texture> digitos;

  std::vector<Herramienta> herramientas;
  std::vector<InventorySlotDto> casilleros;
  int seleccionado;

  static SDL2pp::Rect rect_casillero(int i, int ancho_ventana,
                                     int alto_ventana);

  static void dibujar_icono(SDL2pp::Renderer &renderer,
                            SDL2pp::Texture &textura,
                            const SDL2pp::Rect &origen,
                            const SDL2pp::Rect &casillero);
  void dibujar_item(SDL2pp::Renderer &renderer,
                    const InventorySlotDto &casillero,
                    const SDL2pp::Rect &lugar);
  void dibujar_herramienta(SDL2pp::Renderer &renderer, Herramienta herramienta,
                           const SDL2pp::Rect &lugar);
  void dibujar_numero(SDL2pp::Renderer &renderer, int numero,
                      const SDL2pp::Rect &lugar);

public:
  explicit Inventario(SDL2pp::Renderer &renderer);

  void actualizar(const InventoryDto &inventario);

  void seleccionar(int numero);
  bool click(int x, int y, int ancho_ventana, int alto_ventana);

  bool herramienta_seleccionada(ToolTypeDto &herramienta) const;
  bool item_seleccionado(InventorySlotDto &casillero) const;

  bool indice_item_seleccionado(int &indice) const;

  bool tengo_en_la_mano(Herramienta herramienta) const;

  void dibujar(SDL2pp::Renderer &renderer, int ancho_ventana, int alto_ventana);

  void dibujar_regalo(SDL2pp::Renderer &renderer,
                      const InventorySlotDto &regalo,
                      const SDL2pp::Rect &lugar);

  int contar(ItemTypeDto item, bool solo_calidad_alta) const;
};

#endif
