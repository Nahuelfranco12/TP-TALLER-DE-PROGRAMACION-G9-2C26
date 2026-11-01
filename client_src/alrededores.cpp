#include "alrededores.h"

#include <algorithm>
#include <string>

using namespace SDL2pp;

namespace {
    const int ESCALA = 4;
    const int TILE = 16 * ESCALA;

    const int BOSQUE = 10;
    const int PORCENTAJE_BOSQUE = 50;
    const int SEPARACION = 3;
    const int ARBOLES_POR_GRANJA = 4;
    const int CUADROS = 4;
    const int MS_POR_CUADRO = 250;
    const int SOMBRA = 200;

    const int CASA_ANCHO = 80;
    const int CASA_ALTO = 112;
    const int CASAS_POR_FILA = 3;
    const int MODELOS_CASA = 18;

    // Donde va casa cosa en una granja
    const int CORRAL_Y = 10;
    const int CORRAL_ANCHO = 7;
    const int CORRAL_ALTO = 6;
    const int CAMPO_Y = 10;
    const int CAMPO_ANCHO = 6;
    const int CAMPO_ALTO = 6;

    // La cerca
    const SDL_Rect PIEZAS_CERCA[3] = {
        {21, 48, 16, 16},   // horizontal
        {5, 16, 16, 16},  // vertical
        {21, 48, 6, 16},  // poste
    };

    // Animales y cultivos
    const int VACA_LADO = 32;
    const int GALLINA_LADO = 16;
    const int CULTIVO_LADO = 16;
    const int ULTIMA_ETAPA[4] = {5, 5, 6, 5};
    const int ARADA_X = 4 * 16;
    const int ARADA_Y = 4 * 16;

    const int MARGEN = 8;

    bool lejos_de_la_ventana(int tile_x, int tile_y, int camara_x, int camara_y, int ancho_ventana, int alto_ventana) {
        int x = tile_x * TILE - camara_x;
        int y = tile_y * TILE - camara_y;
        return x < -MARGEN * TILE || y < -MARGEN * TILE || x > ancho_ventana + MARGEN * TILE || x > ancho_ventana + MARGEN * TILE || y < -MARGEN * TILE || y > alto_ventana + MARGEN * TILE;
    }

    int entre(std::mt19937& azar, int minimo, int maximo) {
        std::uniform_int_distribution<int> dado(minimo, maximo);
        return dado(azar);
    }
}

Alrededores::Alrededores(Renderer& renderer, int ancho_granja, int alto_granja, unsigned int semilla)
    : casas(renderer, "assets/edificios/House.png"),
      cerca(renderer, "assets/mapas/ground_01_16x16.png"),
      vaca(renderer, "assets/animales/Female Cow Brown.png"),
      gallina(renderer, "assets/animales/Chicken Blonde  Green.png"),
      cultivos(renderer, "assets/cultivos/Spring Crops.png"),
      suelo(renderer, "assets/mapas/ground_01_16x16.png"),
      arbol(renderer, "assets/mapas/tree1.png"),
      pino(renderer, "assets/mapas/tree1_2.png"),
    ancho_granja(ancho_granja),
    alto_granja(alto_granja) {

    // Texturas de afuera
    casas.SetColorMod(SOMBRA, SOMBRA, SOMBRA);
    cerca.SetColorMod(SOMBRA, SOMBRA, SOMBRA);
    vaca.SetColorMod(SOMBRA, SOMBRA, SOMBRA);
    gallina.SetColorMod(SOMBRA, SOMBRA, SOMBRA);
    cultivos.SetColorMod(SOMBRA, SOMBRA, SOMBRA);
    suelo.SetColorMod(SOMBRA, SOMBRA, SOMBRA);
    arbol.SetColorMod(SOMBRA, SOMBRA, SOMBRA);
    pino.SetColorMod(SOMBRA, SOMBRA, SOMBRA);

    std::mt19937 azar(semilla);

    // Las 8 granjas vecinas
    for (int fila = -1; fila <= 1; fila++) {
        for (int columna = -1; columna <= 1; columna++) {
            if (fila == 0 && columna == 0) {
                continue;
            }
            armar_vecino(azar, columna * (ancho_granja + BOSQUE), fila * (alto_granja + BOSQUE));
        }
    }
    armar_bosque(azar);

    auto por_fila = [](const auto& a, const auto& b) { return a.tile_y < b.tile_y; };
    std::sort(lista_animales.begin(), lista_animales.end(), por_fila);
    std::sort(lista_arboles.begin(), lista_arboles.end(), por_fila);
}

void Alrededores::armar_vecino(std::mt19937& azar, int origen_x, int origen_y) {
    // Casa
    int casa_x = origen_x + entre(azar, 2, 13);
    lista_casas.push_back({casa_x, origen_y + 1, entre(azar, 0, MODELOS_CASA - 1)});

    // Corral
    bool corral_a_la_izquierda = entre(azar, 0, 1) == 0;
    int corral_x = origen_x + (corral_a_la_izquierda ? 2 : 11);
    int campo_x = origen_x + (corral_a_la_izquierda ? 12 : 3);

    // Cerca
    int izquierda = corral_x;
    int derecha = corral_x + CORRAL_ANCHO;
    int arriba = origen_y + CORRAL_Y;
    int abajo = arriba + CORRAL_ALTO;
    int tranquera = izquierda + CORRAL_ANCHO / 2;

    for (int x = izquierda; x < derecha; x++) {
        cercas_atras.push_back({HORIZONTAL, x, arriba});
        cercas_adelante.push_back({x == tranquera ? POSTE : HORIZONTAL, x, abajo});
    }
    cercas_atras.push_back({POSTE, derecha, arriba});
    cercas_adelante.push_back({POSTE, derecha, abajo});
    for (int y = arriba + 1; y < abajo; y++) {
        cercas_atras.push_back({VERTICAL, izquierda, y});
        cercas_adelante.push_back({VERTICAL, derecha, y});
    }

    for (int i = 0; i < 2; i++) {
        lista_animales.push_back({true, izquierda + 1 + i * 2, entre(azar, arriba + 2, abajo - 1), entre(azar, 0, 1) == 0});
    }
    for (int i = 0; i < 3; i++) {
        lista_animales.push_back({false, izquierda + entre(azar, 5, 6), arriba + 1 + i * 2, entre(azar, 0, 1) == 0});
    }

    // Campo
    for (int fila = 0; fila < CAMPO_ALTO; fila++) {
        int tipo = entre(azar, 0, 3);
        for (int columna = 0; columna < CAMPO_ANCHO; columna++) {
            int etapa = entre(azar, 0, ULTIMA_ETAPA[tipo]);
            lista_cultivos.push_back({tipo, etapa, campo_x + columna, origen_y + CAMPO_Y + fila});
        }
    }

    for (int i = 0; i < ARBOLES_POR_GRANJA; i++) {
        int x = origen_x + entre(azar, 1, ancho_granja - 2);
        bool tapa_la_casa = x >= casa_x - 1 && x <= casa_x + CASA_ANCHO / 16;

        if (!tapa_la_casa) {
            lista_arboles.push_back({entre(azar, 0, 1) == 0, x, origen_y + entre(azar, 1, 8)});
        }
    }
}

bool Alrededores::cerca_de_una_granja(int x, int y) const {
    for (int fila = -1; fila <= 1; fila++) {
        for (int columna = -1; columna <= 1; columna++) {
            int origen_x = columna * (ancho_granja + BOSQUE);
            int origen_y = fila * (alto_granja + BOSQUE);
            bool cerca_en_x = x >= origen_x - 1 && x <= origen_x + ancho_granja;
            bool cerca_en_y = y >= origen_y - 1 && y <= origen_y + alto_granja;
            if (cerca_en_x && cerca_en_y) {
                return true;
            }
        }
    }
    return false;
}

void Alrededores::armar_bosque(std::mt19937& azar) {
    int desde_x = -(ancho_granja - BOSQUE);
    int hasta_x = 2 * (ancho_granja + BOSQUE);
    int desde_y = -(alto_granja - BOSQUE);
    int hasta_y = 2 * (alto_granja + BOSQUE);

    for (int y = desde_y; y < hasta_y; y += SEPARACION) {
        for (int x = desde_x; x < hasta_x; x += SEPARACION) {
            int arbol_x = x + entre(azar, 0, SEPARACION - 2);
            int arbol_y = y + entre(azar, 0, SEPARACION - 2);
            bool hay_arbol = entre(azar, 0, 99) < PORCENTAJE_BOSQUE;
            if (hay_arbol && !cerca_de_una_granja(arbol_x, arbol_y)) {
                lista_arboles.push_back({entre(azar, 0, 1) == 0, arbol_x, arbol_y});
            }
        }
    }
}


void Alrededores::dibujar_cerca(Renderer& renderer, const Cerca& pieza, int camara_x, int camara_y) {
    const SDL_Rect& origen = PIEZAS_CERCA[pieza.pieza];
    Rect destino(pieza.tile_x * TILE - camara_x, pieza.tile_y * TILE - camara_y, origen.w * ESCALA, origen.h * ESCALA);
    renderer.Copy(cerca, Rect(origen.x, origen.y, origen.w, origen.h), destino);
}

void Alrededores::dibujar_animal(Renderer& renderer, const Animal& animal, int camara_x, int camara_y) {
    int cuadro = static_cast<int>((SDL_GetTicks() / MS_POR_CUADRO) % CUADROS);
    int flip = animal.mira_a_la_izquierda ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    if (animal.es_vaca) {
        Rect origen(cuadro * VACA_LADO, 0, VACA_LADO, VACA_LADO);
        
        int x = animal.tile_x * TILE - TILE / 2 - camara_x;
        int y = animal.tile_y * TILE - TILE - camara_y;
        renderer.Copy(vaca, origen, Rect(x, y, VACA_LADO * ESCALA, VACA_LADO * ESCALA), 0.0, NullOpt, flip);
    } else { 
        Rect origen(cuadro * GALLINA_LADO, 0, GALLINA_LADO, GALLINA_LADO);
        int x = animal.tile_x * TILE - camara_x;
        int y = animal.tile_y * TILE - camara_y;
        renderer.Copy(gallina, origen, Rect(x, y, GALLINA_LADO * ESCALA, GALLINA_LADO * ESCALA), 0.0, NullOpt, flip);
    }
}


void Alrededores::dibujar_arbol(Renderer& renderer, const Arbol& un_arbol, int camara_x, int camara_y) {
    Texture& textura = un_arbol.es_pino ? pino : arbol;

    int ancho = textura.GetWidth() * ESCALA;
    int alto = textura.GetHeight() * ESCALA;
    int x = un_arbol.tile_x * TILE + TILE / 2 - ancho / 2 - camara_x;
    int y = (un_arbol.tile_y + 1) * TILE - alto - camara_y;

    renderer.Copy(textura, NullOpt, Rect(x, y, ancho, alto));
}

void Alrededores::dibujar(Renderer& renderer, int camara_x, int camara_y, int ancho_ventana, int alto_ventana) {
    // Todo lo que está lejos de la ventana no se dibuja
    auto lejos = [&](int tile_x, int tile_y) { 
        return lejos_de_la_ventana(tile_x, tile_y, camara_x, camara_y, ancho_ventana, alto_ventana); 
    };

// Primero lo del piso, luego lo parado
for (const Cultivo& cultivo : lista_cultivos) {
        if (lejos(cultivo.tile_x, cultivo.tile_y)) {
            continue;
        }
        Rect destino(cultivo.tile_x * TILE - camara_x, cultivo.tile_y * TILE - camara_y, TILE, TILE);
        renderer.Copy(suelo, Rect(ARADA_X, ARADA_Y, CULTIVO_LADO, CULTIVO_LADO), destino);
        int fila = cultivo.tipo * 2 + 1;
        renderer.Copy(cultivos, Rect(cultivo.etapa * CULTIVO_LADO, fila * CULTIVO_LADO, CULTIVO_LADO, CULTIVO_LADO), destino);
    }
for (const Casa& casa : lista_casas) {
        if (lejos(casa.tile_x, casa.tile_y)) {
            continue;
        }
        int fila = casa.modelo / CASAS_POR_FILA;
        int columna = casa.modelo % CASAS_POR_FILA;
        Rect origen(columna * CASA_ANCHO, fila * CASA_ALTO, CASA_ANCHO, CASA_ALTO);
        Rect destino(casa.tile_x * TILE - camara_x, casa.tile_y * TILE - camara_y, CASA_ANCHO * ESCALA, CASA_ALTO * ESCALA);
        renderer.Copy(casas, origen, destino);
    }
for (const Cerca& pieza : cercas_atras) {
        if (lejos(pieza.tile_x, pieza.tile_y)) {
            continue;
        }
        dibujar_cerca(renderer, pieza, camara_x, camara_y);
    }

for (const Animal& animal : lista_animales) {
        if (lejos(animal.tile_x, animal.tile_y)) {
            continue;
        }
        dibujar_animal(renderer, animal, camara_x, camara_y);
    }

for (const Cerca& pieza : cercas_adelante) {
        if (lejos(pieza.tile_x, pieza.tile_y)) {
            continue;
        }
        dibujar_cerca(renderer, pieza, camara_x, camara_y);
    }

for (const Arbol& arbol : lista_arboles) {
        if (lejos(arbol.tile_x, arbol.tile_y)) {
            continue;
        }
        dibujar_arbol(renderer, arbol, camara_x, camara_y);
    }
}