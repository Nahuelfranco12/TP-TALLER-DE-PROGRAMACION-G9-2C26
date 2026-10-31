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

public:
    // Cargo las texturas
    Personaje(SDL2pp::Renderer& renderer);

    // POne al personaje donde dice el servidor (true si se movió)
    bool aplicar(int nuevo_x, int nuevo_y);

    // Avanza la animación de caminar
    void animar(long vueltas);

    // Dónde está (en tiles)
    int obtener_tile_x() const;
    int obtener_tile_y() const;

    // Dibuja el granjero (capas)
    void dibujar(SDL2pp::Renderer& renderer, int camara_x, int camara_y);

    // Cambiar ropa y colores
    void cambiar_pantalon();
    void cambiar_remera();
    void cambiar_pelo();
    void cambiar_sombrero();
    void cambiar_color_pantalon();
    void cambiar_color_pelo();
    void vestir(int nuevo_sombrero, int nuevo_pelo, int nuevo_pantalon, int nueva_remera);
};

#endif
