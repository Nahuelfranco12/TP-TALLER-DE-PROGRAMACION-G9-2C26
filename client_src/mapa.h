#ifndef MAPA_H
#define MAPA_H

#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/game_dtos.h"
#include "decoraciones.h"

class Mapa {
private:
  SDL2pp::Texture suelo;
  SDL2pp::Texture muebles;
  SDL2pp::Texture piso_pueblo;
  SDL2pp::Texture flores;
  SDL2pp::Texture casa;
  std::vector<std::string> filas;
  char borde;

  SectorTypeDto tipo;

  std::vector<std::string> pasto_afuera;
  int margen;
  std::vector<Decoracion> decoraciones;

  void generar_granja(int ancho, int alto, unsigned int semilla);
  void generar_caverna(int ancho, int alto, unsigned int semilla);
  void generar_pueblo(int ancho, int alto, unsigned int semilla);
  void generar_centro(int ancho, int alto);
  void generar_cabana(int ancho, int alto);

  char tile_en(int x, int y) const;

  void dibujar_tile(SDL2pp::Renderer &renderer, char tipo, int x, int y,
                    int lado);

public:
  Mapa(SDL2pp::Renderer &renderer, SectorTypeDto tipo, int ancho, int alto,
       unsigned int semilla);

  int obtener_ancho() const;
  int obtener_alto() const;

  bool es_escalera(int x, int y) const;

  void actualizar(const std::vector<std::vector<TileDto>> &tiles);

  void dibujar_completo(SDL2pp::Renderer &renderer, int origen_x, int origen_y,
                        int lado);
  void dibujar(SDL2pp::Renderer &renderer, int camara_x, int camara_y,
               int ancho_ventana, int alto_ventana, bool incluir_margen = true);

  const std::vector<Decoracion> &obtener_decoraciones() const;
};

#endif
