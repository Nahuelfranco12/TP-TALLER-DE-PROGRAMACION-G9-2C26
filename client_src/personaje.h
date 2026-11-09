#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SDL2pp/SDL2pp.hh>

#include "direccion.h"

// El granjero
class Personaje {
private:
  // Texturas
  SDL2pp::Texture cuerpo;
  SDL2pp::Texture pantalones;
  SDL2pp::Texture remeras;
  SDL2pp::Texture pelos;
  SDL2pp::Texture sombreros;

  // Ropa y colores
  int pantalon;
  int remera;
  int pelo;
  int sombrero;
  int color_pantalon;
  int color_pelo;

  // Posición en tiles
  int tile_x;
  int tile_y;

  // Animación
  Direccion mirando;
  long vueltas_caminando;
  long vueltas_restantes_paso;
  long vueltas_picando;

  void dibujar_capas(SDL2pp::Renderer &renderer, int x, int y, int lado,
                     int columna, int fila_cuerpo, Direccion direccion,
                     int rebote);

public:
  // Cargo las texturas
  explicit Personaje(SDL2pp::Renderer &renderer);

  // POne al personaje donde dice el servidor (true si se movió)
  bool aplicar(int nuevo_x, int nuevo_y);

  // Avanza la animación de caminar
  void animar(long vueltas);

  void mirar(Direccion direccion);

  void picar();
  bool esta_picando() const { return vueltas_picando > 0; }

  // Dónde está (en tiles)
  int obtener_tile_x() const;
  int obtener_tile_y() const;

  Direccion obtener_direccion() const;

  // Dibuja el granjero (capas)
  void dibujar(SDL2pp::Renderer &renderer, int camara_x, int camara_y);

  void dibujar_quieto(SDL2pp::Renderer &renderer, int otro_tile_x,
                      int otro_tile_y, int camara_x, int camara_y, int lado);

  // Cambiar ropa y colores
  void cambiar_pantalon();
  void cambiar_remera();
  void cambiar_pelo();
  void cambiar_sombrero();
  void cambiar_color_pantalon();
  void cambiar_color_pelo();
  void vestir(int nuevo_sombrero, int nuevo_pelo, int nuevo_pantalon,
              int nueva_remera);
};

#endif
