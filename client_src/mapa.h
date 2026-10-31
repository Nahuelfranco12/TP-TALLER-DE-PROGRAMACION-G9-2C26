#ifndef MAPA_H
#define MAPA_H

#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

class Mapa {
private:
    SDL2pp::Texture suelo;
    std::vector<std::string> filas;

    char tile_en(int x, int y) const;

    void dibujar_tile(SDL2pp::Renderer& renderer, char tipo, int x, int y);
public:
    Mapa(SDL2pp::Renderer& renderer, int ancho, int alto, unsigned int semilla);

    int obtener_ancho() const;
    int obtener_alto() const;

    void dibujar(SDL2pp::Renderer& renderer, int camara_x, int camara_y, int ancho_ventana, int alto_ventana);};

#endif