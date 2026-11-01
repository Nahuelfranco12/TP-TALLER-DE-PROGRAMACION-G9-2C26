#ifndef ALREDEDORES_H
#define ALREDEDORES_H

#include <random>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

class Alrededores {
private:
    struct Casa {
        int tile_x;
        int tile_y;
        int modelo;
    };

    struct Animal {
        bool es_vaca;
        int tile_x;
        int tile_y;
        bool mira_a_la_izquierda;
    };

    struct Cultivo {
        int tipo;
        int etapa;
        int tile_x;
        int tile_y;
    };

    enum PiezaCerca {HORIZONTAL, VERTICAL, POSTE};

    struct Cerca {
        PiezaCerca pieza;
        int tile_x;
        int tile_y;
    };

    struct Arbol {
        bool es_pino;
        int tile_x;
        int tile_y;
    };

    SDL2pp::Texture casas;
    SDL2pp::Texture cerca;
    SDL2pp::Texture vaca;
    SDL2pp::Texture gallina;
    SDL2pp::Texture cultivos;
    SDL2pp::Texture suelo;
    SDL2pp::Texture arbol;
    SDL2pp::Texture pino;

    int ancho_granja;
    int alto_granja;

    std::vector<Casa> lista_casas;
    std::vector<Animal> lista_animales;
    std::vector<Cultivo> lista_cultivos;
    std::vector<Cerca> cercas_atras;
    std::vector<Cerca> cercas_adelante;
    std::vector<Arbol> lista_arboles;

    // Sortea todo lo de una granja vecina
    void armar_vecino(std::mt19937& azar, int origen_x, int origen_y);
    void armar_bosque(std::mt19937& azar);

    bool cerca_de_una_granja(int x, int y) const;

    void dibujar_cerca(SDL2pp::Renderer& renderer, const Cerca& pieza, int camara_x, int camara_y);
    void dibujar_animal(SDL2pp::Renderer& renderer, const Animal& animal, int camara_x, int camara_y);
    void dibujar_arbol(SDL2pp::Renderer& renderer, const Arbol& un_arbol, int camara_x, int camara_y);
public:
    Alrededores(SDL2pp::Renderer& renderer, int ancho_granja, int alto_granja, unsigned int semilla);

    void dibujar(SDL2pp::Renderer& renderer, int camara_x, int camara_y, int ancho_ventana, int alto_ventana);
};

#endif
