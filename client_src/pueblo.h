#ifndef PUEBLO_H
#define PUEBLO_H

#include <map>
#include <string>
#include <vector>

#include "../common_src/game_dtos.h"
#include "constantes_sdl.h"

#include <SDL2pp/SDL2pp.hh>

class Personaje;

class Pueblo {
public:
  enum AccionTienda { NINGUNA, COMPRAR, VENDER, HABLAR, SALIR };

private:
  struct Edificio {
    int tile_x;
    int tile_y;
    int ancho;
    int alto;
    int modelo;
  };

  struct Npc {
    int tile_x;
    int tile_y;
    int modelo;
  };

  SDL2pp::Texture edificios;
  SDL2pp::Texture edificio_centro;
  std::vector<SDL2pp::Texture> sprites_npcs;
  std::vector<SDL2pp::Texture> fondos_tiendas;
  SDL2pp::Font fuente;
  std::vector<SDL2pp::Texture> titulos;
  std::vector<SDL2pp::Texture> texto_botones;

  std::vector<Edificio> lista_edificios;
  std::vector<Npc> lista_npcs;

  long vueltas;

  int tienda_abierta;
  long vueltas_en_tienda;
  std::vector<SDL2pp::Rect> botones;

  void dibujar_edificio(SDL2pp::Renderer &renderer, const Edificio &edificio,
                      int camara_x, int camara_y, int lado);

  void dibujar_npc(SDL2pp::Renderer &renderer, const Npc &npc, int camara_x,
                   int camara_y, int lado);

  void dibujar_npc_en(SDL2pp::Renderer &renderer, int modelo, int centro_x,
                      int pie_y, int lado);

public:
  explicit Pueblo(SDL2pp::Renderer &renderer);

  void animar(long vueltas_pasadas);

  void dibujar(SDL2pp::Renderer &renderer, int camara_x, int camara_y,
               int lado = TAMANIO_TILE);

  void actualizar(const std::map<GamePositionDto, EntityDto> &entidades);

  void actualizar_edificios(const std::vector<BuildingDto> &del_servidor);

  bool click_npc(int x, int y, int camara_x, int camara_y, GamePositionDto &posicion);

  AccionTienda click_tienda(int x, int y);

  bool hay_tienda_abierta() const;
  void cerrar_tienda();

  void dibujar_tienda(SDL2pp::Renderer &renderer, Personaje &personaje);
};

#endif
