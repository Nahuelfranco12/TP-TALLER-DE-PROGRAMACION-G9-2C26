#include "inventario.h"

#include <string>

using namespace SDL2pp;

namespace {
    const int MAX_HERRAMIENTAS = 4;
    const int MAX_ITEMS = 9;
    const int CASILLEROS = MAX_HERRAMIENTAS + MAX_ITEMS;

    const int LADO = 44;
    const int SEPARACION = 12;
    const int MARGEN_ABAJO = 10;
    const int ICONO = 32;

    const SDL_Color BLANCO = {255, 255, 255, 255};
}

Inventario::Inventario(Renderer& renderer)
    : minerales(renderer, "assets/inventario/ore.png"),
      cultivos(renderer, "assets/inventario/Spring Crops.png"),
      huevo(renderer, "assets/inventario/egg.png"),
      leche(renderer, "assets/inventario/milk.png"),
      fuente("assets/fuentes/DejaVuSans-Bold.ttf", 11),
      seleccionado(0) {
    for (int i = 0; i <= 9; i++) {
        digitos.emplace_back(renderer, fuente.RenderUTF8_Blended(std::to_string(i), BLANCO));
    }

    iconos_herramienta.emplace_back(renderer, "assets/inventario/pickaxe.png");
    iconos_herramienta.emplace_back(renderer, "assets/inventario/shovel.png");
    iconos_herramienta.emplace_back(renderer, "assets/inventario/axe.png");

    herramientas = {PICO, PALA, HACHA};
    agregar(ITEM_SEMILLA, 10);
    agregar(ITEM_HUEVO, 2);
    agregar(ITEM_LECHE, 1);
}

void Inventario::agregar(TipoItem tipo, int cantidad) {
    for (Casillero& casillero : casilleros) {
        if (casillero.tipo == tipo) {
            casillero.cantidad += cantidad;
            return;
        }
    }
    if (static_cast<int>(casilleros.size()) < MAX_ITEMS) {
        casilleros.push_back({tipo, cantidad});
    }
}

void Inventario::seleccionar(int numero) {
    if (numero >= 0 && numero < CASILLEROS) {
        seleccionado = numero;
    }
}

bool Inventario::click(int x, int y, int ancho_ventana, int alto_ventana) {
    for (int i = 0; i < CASILLEROS; i++) {
        if (rect_casillero(i, ancho_ventana, alto_ventana).Contains(x, y)) {
            seleccionado = i;
            return true;
        }
    }
    return false;
}

bool Inventario::tengo_en_la_mano(Herramienta herramienta) const {
    return seleccionado < static_cast<int>(herramientas.size()) && herramientas[seleccionado] == herramienta;
}

Rect Inventario::rect_casillero(int i, int ancho_ventana, int alto_ventana) const {
    int ancho_barra = CASILLEROS * LADO + SEPARACION;
    int x = (ancho_ventana - ancho_barra) / 2 + i * LADO;
    if (i >= MAX_HERRAMIENTAS) {
        x += SEPARACION;
    }
    int y = alto_ventana - LADO - MARGEN_ABAJO;
    return Rect(x, y, LADO, LADO);
}

void Inventario::dibujar_icono(Renderer& renderer, Texture& textura, const Rect& origen, const Rect& casillero) {
    Rect destino(casillero.x + (LADO - ICONO) / 2, casillero.y + (LADO - ICONO) / 2, ICONO, ICONO);
    renderer.Copy(textura, origen, destino);
}

void Inventario::dibujar_numero(Renderer& renderer, int numero, const Rect& lugar) {
    std::string texto = std::to_string(numero);
    int x = lugar.x + LADO - 3;
    for (int i = static_cast<int>(texto.size()) - 1; i >= 0; i--) {
        Texture& digito = digitos[texto[i] - '0'];
        x -= digito.GetWidth();
        renderer.Copy(digito, NullOpt, Rect(x, lugar.y + LADO - digito.GetHeight() - 1, digito.GetWidth(), digito.GetHeight()));
    }
}

void Inventario::dibujar_item(Renderer& renderer, const Casillero& casillero, const Rect& lugar) {
    switch (casillero.tipo) {
        case ITEM_ORO:
            dibujar_icono(renderer, minerales, Rect(100, 3 * 32 + 17, 10, 10), lugar);
            break;
        case ITEM_HIERRO:
            dibujar_icono(renderer, minerales, Rect(100, 0 * 32 + 17, 10, 10), lugar);
            break;
        case ITEM_LAPISLAZULI:
            dibujar_icono(renderer, minerales, Rect(100, 2 * 32 + 17, 10, 10), lugar);
            break;
        case ITEM_CARBON:
            dibujar_icono(renderer, minerales, Rect(100, 1 * 32 + 17, 10, 10), lugar);
            break;
        case ITEM_SEMILLA:
            dibujar_icono(renderer, cultivos, Rect(7 * 16, 16, 16, 16), lugar);
            break;
        case ITEM_HUEVO:
            dibujar_icono(renderer, huevo, Rect(0, 0, huevo.GetWidth(), huevo.GetHeight()), lugar);
            break;
        case ITEM_LECHE:
            dibujar_icono(renderer, leche, Rect(0, 0, leche.GetWidth(), leche.GetHeight()), lugar);
            break;
        case ITEM_CULTIVO:
            dibujar_icono(renderer, cultivos, Rect(8 * 16, 16, 16, 16), lugar);
            break;
    }
    dibujar_numero(renderer, casillero.cantidad, lugar);
}

void Inventario::dibujar_herramienta(Renderer& renderer, Herramienta herramienta, const Rect& lugar) {
    Texture& icono = iconos_herramienta[static_cast<int>(herramienta)];
    dibujar_icono(renderer, icono, Rect(0, 0, icono.GetWidth(), icono.GetHeight()), lugar);
}

void Inventario::dibujar(Renderer& renderer, int ancho_ventana, int alto_ventana) {
    for (int i = 0; i < CASILLEROS; i++) {
        Rect lugar = rect_casillero(i, ancho_ventana, alto_ventana);

        renderer.SetDrawColor(60, 40, 30, 230);
        renderer.FillRect(lugar);

        if (i < MAX_HERRAMIENTAS) {
            if (i < static_cast<int>(herramientas.size())) {
                dibujar_herramienta(renderer, herramientas[i], lugar);
            }
        } else {
            int item = i - MAX_HERRAMIENTAS;
            if (item < static_cast<int>(casilleros.size())) {
                dibujar_item(renderer, casilleros[item], lugar);
            }
        }

        if (i == seleccionado) {
            renderer.SetDrawColor(255, 200, 40, 255);
            renderer.DrawRect(lugar);
            renderer.DrawRect(Rect(lugar.x + 1, lugar.y + 1, LADO - 2, LADO - 2));
        } else {
            renderer.SetDrawColor(140, 100, 60, 255);
            renderer.DrawRect(lugar);
        }
    }
}