#ifndef CENTRO_COMUNITARIO
#define CENTRO_COMUNITARIO

#include <vector>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "constantes_sdl.h"

class Inventario;

class CentroComunitario {
public:
    enum AccionCentro {NINGUNA, CONSULTAR, CANJEAR, SALIR};
private:
    struct Set {
        int tile_x;
        int tile_y;
        int modelo;
    };

    SDL2pp::Texture ofrendas;
    SDL2pp::Font fuente;
    SDL2pp::Font fuente_chica;
    std::vector<SDL2pp::Texture> titulos;
    SDL2pp::Texture texto_canjear;
    SDL2pp::Texture texto_salir;
    std::vector<Set> lista_sets;

    int set_abierto;
    SDL2pp::Rect boton_canjear;
    SDL2pp::Rect boton_salir;

    std::vector<std::string> lineas;
    std::vector<SDL2pp::Texture> textura_lineas;

    void dibujar_figurin(SDL2pp::Renderer &renderer, const Set &set, int camara_x, int camara_y, int lado);

    std::vector<std::string> armar_lineas(const Inventario &inventario, size_t monedas) const;

    void actualizar_lineas(SDL2pp::Renderer &renderer, const Inventario &inventario, size_t monedas);

    void dibujar_boton(SDL2pp::Renderer &renderer, const SDL2pp::Rect &boton, SDL2pp::Texture &texto);
public:
    explicit CentroComunitario(SDL2pp::Renderer &renderer);

    void dibujar(SDL2pp::Renderer &renderer, int camara_x, int camara_y, int lado = TAMANIO_TILE);

    AccionCentro click_set(int x, int y, int camara_x, int camara_y);

    bool hay_set_abierto() const;
    void cerrar_set();

    void dibujar_set(SDL2pp::Renderer &renderer, const Inventario &inventario, size_t monedas);
};

#endif
