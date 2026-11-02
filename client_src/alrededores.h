#ifndef ALREDEDORES_H
#define ALREDEDORES_H

#include <random>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

class Alrededores {
private:
    struct Arbol {
        bool es_pino;
        int tile_x;
        int tile_y;
    };

    SDL2pp::Texture arbol;
    SDL2pp::Texture pino;

    int ancho_granja;
    int alto_granja;
    
    std::vector<Arbol> lista_arboles;

    bool cerca_de_la_granja(int x, int y) const;

    void dibujar_arbol(SDL2pp::Renderer& renderer, const Arbol& un_arbol, int camara_x, int camara_y);
public:
    Alrededores(SDL2pp::Renderer& renderer, int ancho_granja, int alto_granja, unsigned int semilla);

    void dibujar(SDL2pp::Renderer& renderer, int camara_x, int camara_y, int ancho_ventana, int alto_ventana);
};

#endif
