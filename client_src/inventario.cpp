#include "inventario.h"

#include <string>

#include "constantes_sdl.h"

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;

namespace {
const SDL_Color BLANCO = COLOR_TEXTO;

Rect icono_mineral(int fila) {
  return Rect(ICONO_MINERAL_X, fila * ICONO_MINERAL_CELDA + ICONO_MINERAL_Y,
              ICONO_MINERAL_LADO, ICONO_MINERAL_LADO);
}

Rect icono_cultivo(int columna, int fila) {
  return Rect(columna * ICONO_CULTIVO_LADO, fila * ICONO_CULTIVO_LADO,
              ICONO_CULTIVO_LADO, ICONO_CULTIVO_LADO);
}

int columna_de_cosecha(CropQualityDto calidad) {
  switch (calidad) {
    case CropQualityDto::EXCELENT:
      return ICONO_COSECHA_PLATA_COLUMNA;
    case CropQualityDto::INCREDIBLE:
      return ICONO_COSECHA_ORO_COLUMNA;
    case CropQualityDto::PERFECT:
      return ICONO_COSECHA_IRIDIO_COLUMNA;
    default:
      return ICONO_COSECHA_COLUMNA;
  }
}
} // namespace

Inventario::Inventario(Renderer &renderer)
    : minerales(renderer, RUTA_ICONOS_MINERALES),
      cultivos(renderer, RUTA_ICONOS_CULTIVOS), huevo(renderer, RUTA_HUEVO),
      leche(renderer, RUTA_LECHE), cofre(renderer, RUTA_COFRE),
      interior(renderer, RUTA_INTERIOR), vaca(renderer, RUTA_VACA),
      gallina(renderer, RUTA_GALLINA), fuente(RUTA_FUENTE_JUEGO, INVENTARIO_TAMANIO_LETRA), seleccionado(0) {
  for (int i = 0; i < DIGITOS_DECIMALES; i++) {
    digitos.emplace_back(renderer,
                         fuente.RenderUTF8_Blended(std::to_string(i), BLANCO));
  }

  iconos_herramienta.emplace_back(renderer, RUTA_PICO);
  iconos_herramienta.emplace_back(renderer, RUTA_REGADERA);
  iconos_herramienta.emplace_back(renderer, RUTA_PALA);
  iconos_herramienta.emplace_back(renderer, RUTA_ESPADA);

  herramientas = {PICO, REGADERA, PALA, ESPADA};
}

void Inventario::seleccionar(int numero) {
  if (numero >= 0 && numero < INVENTARIO_CASILLEROS) {
    seleccionado = numero;
  }
}

bool Inventario::click(int x, int y, int ancho_ventana, int alto_ventana) {
  for (int i = 0; i < INVENTARIO_CASILLEROS; i++) {
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
  int item = seleccionado - INVENTARIO_HERRAMIENTAS;
  if (item < 0 || item >= static_cast<int>(casilleros.size()))
    return false;
  casillero = casilleros[item];
  return true;
}

Rect Inventario::rect_casillero(int i, int ancho_ventana, int alto_ventana) {
  int ancho_barra =
      INVENTARIO_CASILLEROS * INVENTARIO_LADO_CASILLERO + INVENTARIO_SEPARACION;
  int x = (ancho_ventana - ancho_barra) / 2 + i * INVENTARIO_LADO_CASILLERO;
  if (i >= INVENTARIO_HERRAMIENTAS) {
    x += INVENTARIO_SEPARACION;
  }
  int y = alto_ventana - INVENTARIO_LADO_CASILLERO - INVENTARIO_MARGEN_ABAJO;
  return Rect(x, y, INVENTARIO_LADO_CASILLERO, INVENTARIO_LADO_CASILLERO);
}

void Inventario::dibujar_icono(Renderer &renderer, Texture &textura,
                               const Rect &origen, const Rect &casillero) {
  int margen = (INVENTARIO_LADO_CASILLERO - INVENTARIO_LADO_ICONO) / 2;
  Rect destino(casillero.x + margen, casillero.y + margen,
               INVENTARIO_LADO_ICONO, INVENTARIO_LADO_ICONO);
  renderer.Copy(textura, origen, destino);
}

void Inventario::dibujar_numero(Renderer &renderer, int numero,
                                const Rect &lugar) {
  std::string texto = std::to_string(numero);
  int x = lugar.x + INVENTARIO_LADO_CASILLERO - INVENTARIO_NUMERO_MARGEN_X;
  for (int i = static_cast<int>(texto.size()) - 1; i >= 0; i--) {
    Texture &digito = digitos[texto[i] - '0'];
    x -= digito.GetWidth();
    int y = lugar.y + INVENTARIO_LADO_CASILLERO - digito.GetHeight() -
            INVENTARIO_NUMERO_MARGEN_Y;
    renderer.Copy(digito, NullOpt,
                  Rect(x, y, digito.GetWidth(), digito.GetHeight()));
  }
}

void Inventario::dibujar_item(Renderer &renderer,
                              const InventorySlotDto &casillero,
                              const Rect &lugar) {
  switch (casillero.item) {
  case ItemTypeDto::MINERAL_GOLD:
    dibujar_icono(renderer, minerales, icono_mineral(ICONO_MINERAL_FILA_ORO),
                  lugar);
    break;
  case ItemTypeDto::MINERAL_IRON:
    dibujar_icono(renderer, minerales, icono_mineral(ICONO_MINERAL_FILA_HIERRO),
                  lugar);
    break;
  case ItemTypeDto::MINERAL_LAPIZLAZULI:
    dibujar_icono(renderer, minerales,
                  icono_mineral(ICONO_MINERAL_FILA_LAPISLAZULI), lugar);
    break;
  case ItemTypeDto::MINERAL_COAL:
    dibujar_icono(renderer, minerales, icono_mineral(ICONO_MINERAL_FILA_CARBON),
                  lugar);
    break;
  case ItemTypeDto::CHICKEN_EGG:
    dibujar_icono(renderer, huevo,
                  Rect(0, 0, huevo.GetWidth(), huevo.GetHeight()), lugar);
    break;
  case ItemTypeDto::COW_MILK:
    dibujar_icono(renderer, leche,
                  Rect(0, 0, leche.GetWidth(), leche.GetHeight()), lugar);
    break;

  // Semillas
  case ItemTypeDto::SEED_STRAWBERRY:
    dibujar_icono(
        renderer, cultivos,
        icono_cultivo(ICONO_SEMILLA_COLUMNA, ICONO_CULTIVO_FILA_FRUTILLA),
        lugar);
    break;
  case ItemTypeDto::SEED_GREEN_ONION:
    dibujar_icono(
        renderer, cultivos,
        icono_cultivo(ICONO_SEMILLA_COLUMNA, ICONO_CULTIVO_FILA_CEBOLLA),
        lugar);
    break;
  case ItemTypeDto::SEED_POTATO:
    dibujar_icono(renderer, cultivos,
                  icono_cultivo(ICONO_SEMILLA_COLUMNA, ICONO_CULTIVO_FILA_PAPA),
                  lugar);
    break;
  case ItemTypeDto::SEED_PUMPKIN:
    dibujar_icono(
        renderer, cultivos,
        icono_cultivo(ICONO_SEMILLA_COLUMNA, ICONO_CULTIVO_FILA_CALABAZA),
        lugar);
    break;

  case ItemTypeDto::CROP_STRAWBERRY:
    dibujar_icono(
        renderer, cultivos,
        icono_cultivo(columna_de_cosecha(casillero.quality), ICONO_CULTIVO_FILA_FRUTILLA),
        lugar);
    break;
  case ItemTypeDto::CROP_GREEN_ONION:
    dibujar_icono(
        renderer, cultivos,
        icono_cultivo(columna_de_cosecha(casillero.quality), ICONO_CULTIVO_FILA_CEBOLLA),
        lugar);
    break;
  case ItemTypeDto::CROP_POTATO:
    dibujar_icono(renderer, cultivos,
                  icono_cultivo(columna_de_cosecha(casillero.quality), ICONO_CULTIVO_FILA_PAPA),
                  lugar);
    break;
  case ItemTypeDto::CROP_PUMPKIN:
    dibujar_icono(
        renderer, cultivos,
        icono_cultivo(columna_de_cosecha(casillero.quality), ICONO_CULTIVO_FILA_CALABAZA),
        lugar);
    break;
  case ItemTypeDto::CHEST:
    dibujar_icono(renderer, cofre, Rect(SPRITE_COFRE_X, SPRITE_COFRE_CERRADO_Y, SPRITE_COFRE_LADO, SPRITE_COFRE_LADO), lugar);
    break;
  case ItemTypeDto::ANIMAL_COW:
    dibujar_icono(renderer, vaca,
                  Rect(0, 0, SPRITE_VACA_LADO, SPRITE_VACA_LADO), lugar);
    break;
  case ItemTypeDto::ANIMAL_CHICKEN:
    dibujar_icono(renderer, gallina,
                  Rect(0, 0, SPRITE_GALLINA_LADO, SPRITE_GALLINA_LADO), lugar);
    break;
  case ItemTypeDto::BED: {
    int alto = INVENTARIO_LADO_ICONO;
    int ancho = SPRITE_CAMA_ANCHO * alto / SPRITE_CAMA_ALTO;
    Rect destino(lugar.x + (INVENTARIO_LADO_CASILLERO - ancho) / 2, lugar.y + (INVENTARIO_LADO_CASILLERO - alto) / 2, ancho, alto);
    renderer.Copy(interior,Rect(SPRITE_CAMA_X, SPRITE_CAMA_Y, SPRITE_CAMA_ANCHO, SPRITE_CAMA_ALTO), destino);
    break;
  }
  default:
    break;
  }
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
  const SDL2pp::Color fondo = COLOR_CASILLERO;
  const SDL2pp::Color seleccion = COLOR_CASILLERO_SELECCIONADO;
  const SDL2pp::Color borde = COLOR_CASILLERO_BORDE;
  for (int i = 0; i < INVENTARIO_CASILLEROS; i++) {
    Rect lugar = rect_casillero(i, ancho_ventana, alto_ventana);

    renderer.SetDrawColor(fondo);
    renderer.FillRect(lugar);

    if (i < INVENTARIO_HERRAMIENTAS) {
      if (i < static_cast<int>(herramientas.size())) {
        dibujar_herramienta(renderer, herramientas[i], lugar);
      }
    } else {
      int item = i - INVENTARIO_HERRAMIENTAS;
      if (item < static_cast<int>(casilleros.size())) {
        dibujar_item(renderer, casilleros[item], lugar);
      }
    }

    if (i == seleccionado) {
      renderer.SetDrawColor(seleccion);
      renderer.DrawRect(lugar);
      renderer.DrawRect(Rect(lugar.x + 1, lugar.y + 1,
                             INVENTARIO_LADO_CASILLERO - 2,
                             INVENTARIO_LADO_CASILLERO - 2));
    } else {
      renderer.SetDrawColor(borde);
      renderer.DrawRect(lugar);
    }
  }
}

bool Inventario::indice_item_seleccionado(int &indice) const {
  int item = seleccionado - INVENTARIO_HERRAMIENTAS;
  if (item < 0 || item >= static_cast<int>(casilleros.size()))
    return false;
  indice = item;
  return true;
}

void Inventario::actualizar(const InventoryDto &inventario) {
  casilleros.clear();
  for (const InventorySlotDto &slot : inventario.slots) {
    if (static_cast<int>(casilleros.size()) == INVENTARIO_ITEMS)
      break;
    casilleros.push_back(slot);
  }
}

void Inventario::dibujar_regalo(Renderer &renderer,
                                const InventorySlotDto &regalo,
                                const Rect &lugar) {
  dibujar_item(renderer, regalo, lugar);
}

int Inventario::contar(ItemTypeDto item, bool solo_calidad_alta) const {
  int total = 0;
  for (const InventorySlotDto &casillero : casilleros) {
    if (casillero.item != item) {
      continue;
    }
    if (solo_calidad_alta) {
      bool es_alta = casillero.quality == CropQualityDto::INCREDIBLE || casillero.quality == CropQualityDto::PERFECT;
      if (!es_alta) {
        continue;
      }
    }
    total += static_cast<int>(casillero.count);
  }
  return total;
}
