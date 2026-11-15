#include "inventario.h"

#include <string>

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;

namespace {
const int MAX_HERRAMIENTAS = 4;
const int MAX_ITEMS = 9;
const int CASILLEROS = MAX_HERRAMIENTAS + MAX_ITEMS;

const int LADO = 44;
const int SEPARACION = 12;
const int MARGEN_ABAJO = 10;
const int ICONO = 32;

const SDL_Color BLANCO = {255, 255, 255, 255};
} // namespace

Inventario::Inventario(Renderer &renderer)
    : minerales(renderer, "assets/inventario/ore.png"),
      cultivos(renderer, "assets/inventario/Spring Crops.png"),
      huevo(renderer, "assets/inventario/egg.png"),
      leche(renderer, "assets/inventario/milk.png"),
      fuente("assets/fuentes/DejaVuSans-Bold.ttf", 11), seleccionado(0) {
  for (int i = 0; i <= 9; i++) {
    digitos.emplace_back(renderer,
                         fuente.RenderUTF8_Blended(std::to_string(i), BLANCO));
  }

  iconos_herramienta.emplace_back(renderer, "assets/inventario/pickaxe.png");
  iconos_herramienta.emplace_back(renderer,
                                  "assets/inventario/watering_can.png");
  iconos_herramienta.emplace_back(renderer, "assets/inventario/shovel.png");
  iconos_herramienta.emplace_back(renderer, "assets/inventario/sword.png");

  herramientas = {PICO, REGADERA, PALA, ESPADA};
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
  return seleccionado < static_cast<int>(herramientas.size()) &&
         herramientas[seleccionado] == herramienta;
}

bool Inventario::herramienta_seleccionada(ToolTypeDto &herramienta) const {
  if (seleccionado >= static_cast<int>(herramientas.size())) {
    herramienta = static_cast<ToolTypeDto>(seleccionado);
    return false;
  }
  switch (herramientas[seleccionado]) {
  case PICO:
    herramienta = ToolTypeDto::PICKAXE;
    break;
  case REGADERA:
    herramienta = ToolTypeDto::WATERING_CAN;
    break;
  case PALA:
    herramienta = ToolTypeDto::SHOVEL;
    break;
  case ESPADA:
    herramienta = ToolTypeDto::SWORD;
    break;
  }
  return true;
}

bool Inventario::item_seleccionado(InventorySlotDto &casillero) const {
  int item = seleccionado - MAX_HERRAMIENTAS;
  if (item < 0 || item >= static_cast<int>(casilleros.size()))
    return false;
  casillero = casilleros[item];
  return true;
}

Rect Inventario::rect_casillero(int i, int ancho_ventana, int alto_ventana) {
  int ancho_barra = CASILLEROS * LADO + SEPARACION;
  int x = (ancho_ventana - ancho_barra) / 2 + i * LADO;
  if (i >= MAX_HERRAMIENTAS) {
    x += SEPARACION;
  }
  int y = alto_ventana - LADO - MARGEN_ABAJO;
  return Rect(x, y, LADO, LADO);
}

void Inventario::dibujar_icono(Renderer &renderer, Texture &textura,
                               const Rect &origen, const Rect &casillero) {
  Rect destino(casillero.x + (LADO - ICONO) / 2,
               casillero.y + (LADO - ICONO) / 2, ICONO, ICONO);
  renderer.Copy(textura, origen, destino);
}

void Inventario::dibujar_numero(Renderer &renderer, int numero,
                                const Rect &lugar) {
  std::string texto = std::to_string(numero);
  int x = lugar.x + LADO - 3;
  for (int i = static_cast<int>(texto.size()) - 1; i >= 0; i--) {
    Texture &digito = digitos[texto[i] - '0'];
    x -= digito.GetWidth();
    renderer.Copy(digito, NullOpt,
                  Rect(x, lugar.y + LADO - digito.GetHeight() - 1,
                       digito.GetWidth(), digito.GetHeight()));
  }
}

void Inventario::dibujar_calidad(Renderer &renderer, CropQualityDto calidad,
                                 const Rect &lugar) {
  SDL2pp::Color color(0, 0, 0, 255);
  switch (calidad) {
  case CropQualityDto::GOOD:
    color = SDL2pp::Color(205, 127, 50, 255);
    break;
  case CropQualityDto::EXCELENT:
    color = SDL2pp::Color(200, 200, 215, 255);
    break;
  case CropQualityDto::INCREDIBLE:
    color = SDL2pp::Color(240, 200, 40, 255);
    break;
  case CropQualityDto::PERFECT:
    color = SDL2pp::Color(170, 90, 220, 255);
    break;
  default:
    return;
  }

  // Estrellita
  int x = lugar.x + 3;
  int y = lugar.y + 3;

  // Borde negro
  renderer.SetDrawColor(0, 0, 0, 255);
  renderer.FillRect(Rect(x - 1, y + 2, 10, 4));
  renderer.FillRect(Rect(x + 2, y - 1, 4, 10));

  renderer.SetDrawColor(color);
  renderer.FillRect(Rect(x, y + 3, 8, 2));
  renderer.FillRect(Rect(x + 3, y, 2, 8));
  renderer.FillRect(Rect(x + 2, y + 2, 4, 4));
}

void Inventario::dibujar_item(Renderer &renderer,
                              const InventorySlotDto &casillero,
                              const Rect &lugar) {
  switch (casillero.item) {
  case ItemTypeDto::MINERAL_GOLD:
    dibujar_icono(renderer, minerales, Rect(100, 3 * 32 + 17, 10, 10), lugar);
    break;
  case ItemTypeDto::MINERAL_IRON:
    dibujar_icono(renderer, minerales, Rect(100, 0 * 32 + 17, 10, 10), lugar);
    break;
  case ItemTypeDto::MINERAL_LAPIZLAZULI:
    dibujar_icono(renderer, minerales, Rect(100, 2 * 32 + 17, 10, 10), lugar);
    break;
  case ItemTypeDto::MINERAL_COAL:
    dibujar_icono(renderer, minerales, Rect(100, 1 * 32 + 17, 10, 10), lugar);
    break;
  case ItemTypeDto::CHICKEN_EGG:
    dibujar_icono(renderer, huevo,
                  Rect(0, 0, huevo.GetWidth(), huevo.GetHeight()), lugar);
    break;
  case ItemTypeDto::COW_MILK:
    dibujar_icono(renderer, leche,
                  Rect(0, 0, leche.GetWidth(), leche.GetHeight()), lugar);
    break;

  // SEMILLAS (revisar)
  case ItemTypeDto::SEED_STRAWBERRY:
    dibujar_icono(renderer, cultivos, Rect(7 * 16, 1 * 16, 16, 16), lugar);
    break;
  case ItemTypeDto::SEED_GREEN_ONION:
    dibujar_icono(renderer, cultivos, Rect(7 * 16, 3 * 16, 16, 16), lugar);
    break;
  case ItemTypeDto::SEED_POTATO:
    dibujar_icono(renderer, cultivos, Rect(7 * 16, 5 * 16, 16, 16), lugar);
    break;
  case ItemTypeDto::SEED_PUMPKIN:
    dibujar_icono(renderer, cultivos, Rect(7 * 16, 7 * 16, 16, 16), lugar);
    break;
  // PLANTAS COSECHADAS (tambien revisar)
  case ItemTypeDto::CROP_STRAWBERRY:
    dibujar_icono(renderer, cultivos, Rect(8 * 16, 1 * 16, 16, 16), lugar);
    break;
  case ItemTypeDto::CROP_GREEN_ONION:
    dibujar_icono(renderer, cultivos, Rect(8 * 16, 3 * 16, 16, 16), lugar);
    break;
  case ItemTypeDto::CROP_POTATO:
    dibujar_icono(renderer, cultivos, Rect(8 * 16, 5 * 16, 16, 16), lugar);
    break;
  case ItemTypeDto::CROP_PUMPKIN:
    dibujar_icono(renderer, cultivos, Rect(8 * 16, 7 * 16, 16, 16), lugar);
    break;
  default:
    break;
  }
  dibujar_calidad(renderer, casillero.quality, lugar);
  dibujar_numero(renderer, casillero.count, lugar);
}

void Inventario::dibujar_herramienta(Renderer &renderer,
                                     Herramienta herramienta,
                                     const Rect &lugar) {
  Texture &icono = iconos_herramienta[static_cast<int>(herramienta)];
  dibujar_icono(renderer, icono,
                Rect(0, 0, icono.GetWidth(), icono.GetHeight()), lugar);
}

void Inventario::dibujar(Renderer &renderer, int ancho_ventana,
                         int alto_ventana) {
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

bool Inventario::indice_item_seleccionado(int &indice) const {
  int item = seleccionado - MAX_HERRAMIENTAS;
  if (item < 0 || item >= static_cast<int>(casilleros.size()))
    return false;
  indice = item;
  return true;
}

void Inventario::actualizar(const InventoryDto &inventario) {
  casilleros.clear();
  for (const InventorySlotDto &slot : inventario.slots) {
    if (static_cast<int>(casilleros.size()) == MAX_ITEMS)
      break;
    casilleros.push_back(slot);
  }
}

void Inventario::dibujar_regalo(Renderer &renderer,
                                const InventorySlotDto &regalo,
                                const Rect &lugar) {
  dibujar_item(renderer, regalo, lugar);
}