#ifndef MAPA_H
#define MAPA_H

#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

enum TipoMapa {MAPA_GRANJA, MAPA_CAVERNA};

class Mapa {
private:
    SDL2pp::Texture suelo;
    std::vector<std::string> filas;
    char borde;

    void generar_granja(int ancho, int alto, unsigned int semilla);
    void generar_caverna(int ancho, int alto, unsigned int semilla);

  char tile_en(int x, int y) const;

  void dibujar_tile(SDL2pp::Renderer &renderer, char tipo, int x, int y);

    void dibujar_tile(SDL2pp::Renderer& renderer, char tipo, int x, int y, int lado);
public:
    Mapa(SDL2pp::Renderer& renderer, TipoMapa tipo, int ancho, int alto, unsigned int semilla);

  int obtener_ancho() const;
  int obtener_alto() const;

    bool es_escalera(int x, int y) const;

    void dibujar_completo(SDL2pp::Renderer& renderer, int origen_x, int origen_y, int lado);
    void dibujar(SDL2pp::Renderer& renderer, int camara_x, int camara_y, int ancho_ventana, int alto_ventana);};

#endif
