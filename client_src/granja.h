#ifndef GRANJA_H
#define GRANJA_H

#include <map>
#include <vector>

#include "../common_src/game_dtos.h"
#include "constantes_sdl.h"

#include <SDL2pp/SDL2pp.hh>

class Granja {
private:
  struct Casa {
    int tile_x;
    int tile_y;
    int ancho;
    int alto;
    int modelo;
  };

  enum TipoAnimal { VACA, GALLINA };

  enum TipoCultivo { FRUTILLA, CEBOLLA_DE_VERDEO, PAPA, CALABAZA };

  enum TipoMueble { COFRE, CAMA };

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

  struct Mueble {
    TipoMueble tipo;
    int tile_x;
    int tile_y;
    bool abierto;
  };

  SDL2pp::Texture casas;
  SDL2pp::Texture vaca;
  SDL2pp::Texture gallina;
  SDL2pp::Texture cultivos;
  SDL2pp::Texture suelo;
  SDL2pp::Texture huevo;
  SDL2pp::Texture leche;
  SDL2pp::Texture cofre;
  SDL2pp::Texture interior;

  std::vector<Casa> lista_casas;
  std::vector<Animal> lista_animales;
  std::vector<Cultivo> lista_cultivos;
  std::vector<Mueble> lista_muebles;

  long vueltas;

  void dibujar_casa(SDL2pp::Renderer &renderer, const Casa &casa, int camara_x,
                    int camara_y, int lado);
  void dibujar_cultivo(SDL2pp::Renderer &renderer, const Cultivo &cultivo,
                       int camara_x, int camara_y, int lado);
  void dibujar_animal(SDL2pp::Renderer &renderer, const Animal &animal,
                      int camara_x, int camara_y, int lado);
  void dibujar_producto(SDL2pp::Renderer &renderer, SDL2pp::Texture &producto,
                        int centro_x, int arriba_y, int lado);
  void dibujar_mueble(SDL2pp::Renderer &renderer, const Mueble &mueble,
                      int camara_x, int camara_y, int lado);

public:
  explicit Granja(SDL2pp::Renderer &renderer);

  void animar(long vueltas_pasadas);

  void dibujar(SDL2pp::Renderer &renderer, int camara_x, int camara_y,
               int lado = TAMANIO_TILE);

  void actualizar(const std::map<GamePositionDto, EntityDto> &entidades);

  void actualizar_edificios(const std::vector<BuildingDto> &del_servidor);
};

#endif
