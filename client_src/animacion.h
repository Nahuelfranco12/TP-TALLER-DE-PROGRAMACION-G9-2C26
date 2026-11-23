#ifndef ANIMACION_H
#define ANIMACION_H

#include <string>

#include <SDL2pp/SDL2pp.hh>

class Animacion {
private:
  SDL2pp::Texture textura;
  int lado_cuadro;
  int fila_pie;
  int columna_centro;
  long vueltas_por_cuadro;

  int limitar(long cuadro) const;

public:
  Animacion(SDL2pp::Renderer &renderer, const std::string &ruta, int lado,
            int pie, int centro_x, long vueltas);

  int cuadros() const;

  long duracion() const;

  int cuadro_en_bucle(long vueltas_totales) const;

  int cuadro_de_pasada(long vueltas_restantes) const;

  int cuadro_al_reves(long vueltas_restantes) const;

  int ultimo_cuadro() const;

  void dibujar(SDL2pp::Renderer &renderer, int cuadro, int tile_x, int tile_y,
               int camara_x, int camara_y, int lado_tile, bool espejada,
               const SDL2pp::Color &tinte);
};

#endif
