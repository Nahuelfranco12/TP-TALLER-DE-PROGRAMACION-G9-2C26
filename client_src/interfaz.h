#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <SDL2pp/SDL2pp.hh>

#include "audio.h"

class Interfaz {
private:
    SDL2pp::Font fuente;

    SDL2pp::Texture texto_musica;
    SDL2pp::Texture texto_menos;
    SDL2pp::Texture texto_mas;

    SDL2pp::Rect boton_musica;
    SDL2pp::Rect boton_menos;
    SDL2pp::Rect boton_mas;

    void dibujar_boton(SDL2pp::Renderer& renderer, const SDL2pp::Rect& boton, SDL2pp::Texture& texto);
public:
    explicit Interfaz(SDL2pp::Renderer& renderer);

    bool click(int x, int y, Audio& audio);

    void dibujar(SDL2pp::Renderer& renderer, const Audio& audio);
};
#endif