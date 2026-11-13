#ifndef GRANJA_H
#define GRANJA_H

#include <vector>
#include <map>

#include "../common_src/game_dtos.h"

#include <SDL2pp/SDL2pp.hh>

class Granja {
private:
  struct Casa {
    int tile_x;
    int tile_y;
    int modelo;
  };

  enum TipoAnimal { VACA, GALLINA };

  enum TipoCultivo { FRUTILLA, CEBOLLA_DE_VERDEO, PAPA, CALABAZA };

  struct Animal {
    TipoAnimal tipo;
    int tile_x;
    int tile_y;
    bool mira_a_la_izquierda;
    bool listo;
  };

  struct Cultivo {
    TipoCultivo tipo;
    int tile_x;
    int tile_y;
    int etapa;
  };

  SDL2pp::Texture casas;
  SDL2pp::Texture vaca;
  SDL2pp::Texture gallina;
  SDL2pp::Texture cultivos;
  SDL2pp::Texture suelo;
  SDL2pp::Texture huevo;
  SDL2pp::Texture leche;

  std::vector<Casa> lista_casas;
  std::vector<Animal> lista_animales;
  std::vector<Cultivo> lista_cultivos;

  long vueltas;

  void dibujar_casa(SDL2pp::Renderer &renderer, const Casa &casa, int camara_x, int camara_y, int lado);
  void dibujar_cultivo(SDL2pp::Renderer &renderer, const Cultivo &cultivo, int camara_x, int camara_y, int lado);
  void dibujar_animal(SDL2pp::Renderer &renderer, const Animal &animal, int camara_x, int camara_y, int lado);
  void dibujar_producto(SDL2pp::Renderer &renderer, SDL2pp::Texture &producto, int centro_x, int arriba_y, int lado);

public:
  explicit Granja(SDL2pp::Renderer &renderer);

  void animar(long vueltas_pasadas);

  void dibujar(SDL2pp::Renderer &renderer, int camara_x, int camara_y, int lado = 64);

  void actualizar(const std::map<GamePositionDto, EntityDto> &entidades);
};

#endif
