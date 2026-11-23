#include "pueblo.h"
#include "personaje.h"

#include <algorithm>

#include <SDL2/SDL.h>

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;

namespace {
const SDL_Rect MODELOS_PUESTOS[] = SPRITE_MODELOS_PUESTOS;
const SDL_Rect EDIFICIO_CENTRO = SPRITE_EDIFICIO_CENTRO;

struct ModeloNpc {
  const char *archivo;
  int lado_cuadro;
  int pie_y;
};

const ModeloNpc MODELOS_NPCS[] = SPRITE_MODELOS_NPCS;

const SDL2pp::Color BLANCO = COLOR_TEXTO;

const char *TITULOS[] = TITULOS_TIENDAS;

const char *FONDOS_TIENDAS[] = RUTAS_FONDOS_TIENDAS;

const char *TEXTOS_BOTONES[] = TEXTOS_BOTONES_TIENDA;

int tile_de_pixel(int pixel) {
  int tile = pixel / TAMANIO_TILE;
  if (pixel < 0 && pixel % TAMANIO_TILE != 0) {
    tile--;
  }
  return tile;
}

bool modelo_de_npc(EntityTypeDto tipo, int &modelo) {
  switch (tipo) {
  case EntityTypeDto::NPC_PIERRE:
    modelo = TIENDA_PIERRE;
    return true;
  case EntityTypeDto::NPC_CLINT:
    modelo = TIENDA_CLINT;
    return true;
  case EntityTypeDto::NPC_ROBIN:
    modelo = TIENDA_ROBIN;
    return true;
  case EntityTypeDto::NPC_MARNIE:
    modelo = TIENDA_MARNIE;
    return true;
  default:
    return false;
  }
}

bool modelo_de_edificio(BuildingTypeDto tipo, int &modelo) {
  switch (tipo) {
  case BuildingTypeDto::SHOP_PIERRE:
    modelo = TIENDA_PIERRE;
    return true;
  case BuildingTypeDto::SHOP_CLINT:
    modelo = TIENDA_CLINT;
    return true;
  case BuildingTypeDto::SHOP_ROBIN:
    modelo = TIENDA_ROBIN;
    return true;
  case BuildingTypeDto::SHOP_MARNIE:
    modelo = TIENDA_MARNIE;
    return true;
  case BuildingTypeDto::COMUNITARY_CENTRE:
    modelo = PUEBLO_MODELO_CENTRO;
    return true;
  default:
    return false;
  }
}
} // namespace

Pueblo::Pueblo(Renderer &renderer)
    : edificios(renderer, RUTA_EDIFICIOS_PUEBLO),
      edificio_centro(renderer, RUTA_EDIFICIO_CENTRO_COMUNITARIO),
      fuente(RUTA_FUENTE_JUEGO, TIENDA_TAMANIO_LETRA), vueltas(0),
      tienda_abierta(TIENDA_CERRADA) {

  for (const ModeloNpc &modelo : MODELOS_NPCS) {
    // cppcheck-suppress useStlAlgorithm
    sprites_npcs.emplace_back(renderer, modelo.archivo);
  }

  for (const char *titulo : TITULOS) {
    // cppcheck-suppress useStlAlgorithm
    titulos.emplace_back(renderer, fuente.RenderUTF8_Blended(titulo, BLANCO));
  }
  for (const char *texto : TEXTOS_BOTONES) {
    // cppcheck-suppress useStlAlgorithm
    texto_botones.emplace_back(renderer, fuente.RenderUTF8_Blended(texto, BLANCO));
  }
  botones.resize(TIENDA_CANTIDAD_BOTONES);
  for (const char *archivo : FONDOS_TIENDAS) {
    // cppcheck-suppress useStlAlgorithm
    fondos_tiendas.emplace_back(renderer, archivo);
  }
}

void Pueblo::animar(long vueltas_pasadas) { vueltas += vueltas_pasadas; }

void Pueblo::dibujar_edificio(Renderer &renderer, const Edificio &edificio,
                            int camara_x, int camara_y, int lado) {
  Texture *textura = &edificios;
  SDL_Rect modelo = EDIFICIO_CENTRO;
  if (edificio.modelo == PUEBLO_MODELO_CENTRO) {
    textura = &edificio_centro;
  } else {
    modelo = MODELOS_PUESTOS[edificio.modelo];
  }

  int ancho = edificio.ancho * lado;
  int alto = modelo.h * ancho / modelo.w;
  int x = edificio.tile_x * lado - camara_x;
  int pie = (edificio.tile_y + edificio.alto) * lado - camara_y;
  renderer.Copy(*textura, Rect(modelo.x, modelo.y, modelo.w, modelo.h), Rect(x, pie - alto, ancho, alto));
}

void Pueblo::dibujar_npc_en(Renderer &renderer, int modelo, int centro_x,
                            int pie_y, int lado) {
  const ModeloNpc &datos = MODELOS_NPCS[modelo];

  int cuadro = static_cast<int>((vueltas / NPC_VUELTAS_POR_CUADRO) %
                                NPC_CUADROS_ANIMACION);
  Rect origen(cuadro * datos.lado_cuadro, 0, datos.lado_cuadro,
              datos.lado_cuadro);

  int tamanio = datos.lado_cuadro * lado / PIXELES_POR_TILE;
  int pie = datos.pie_y * lado / PIXELES_POR_TILE;
  renderer.Copy(sprites_npcs[modelo], origen,
                Rect(centro_x - tamanio / 2, pie_y - pie, tamanio, tamanio));
}

void Pueblo::dibujar_npc(Renderer &renderer, const Npc &npc, int camara_x,
                         int camara_y, int lado) {
  int centro_x = npc.tile_x * lado + lado / 2 - camara_x;
  int pie_y = (npc.tile_y + 1) * lado - camara_y;
  dibujar_npc_en(renderer, npc.modelo, centro_x, pie_y, lado);
}

void Pueblo::dibujar(Renderer &renderer, int camara_x, int camara_y, int lado) {
  for (const Edificio &edificio : lista_edificios) {
    dibujar_edificio(renderer, edificio, camara_x, camara_y, lado);
  }
  for (const Npc &npc : lista_npcs) {
    dibujar_npc(renderer, npc, camara_x, camara_y, lado);
  }
}

// cppcheck-suppress functionStatic
void Pueblo::actualizar(const std::map<GamePositionDto, EntityDto> &entidades) {
  lista_npcs.clear();
  for (const auto &[posicion, entidad] : entidades) {
    int modelo = TIENDA_CERRADA;
    if (modelo_de_npc(entidad.type, modelo))
      lista_npcs.push_back({static_cast<int>(posicion.x), static_cast<int>(posicion.y), modelo});
  }
}

void Pueblo::actualizar_edificios(const std::vector<BuildingDto> &del_servidor) {
  lista_edificios.clear();
  for (const BuildingDto &edificio : del_servidor) {
    int modelo = TIENDA_CERRADA;
    if (modelo_de_edificio(edificio.type, modelo)) {
      lista_edificios.push_back({static_cast<int>(edificio.topLeft.x),
                                 static_cast<int>(edificio.topLeft.y),
                                 static_cast<int>(edificio.width),
                                 static_cast<int>(edificio.height), modelo});
    }
  }
}

bool Pueblo::click_npc(int x, int y, int camara_x, int camara_y, GamePositionDto &posicion) {
  int tile_x = tile_de_pixel(x + camara_x);
  int tile_y = tile_de_pixel(y + camara_y);

  for (const Npc &npc : lista_npcs) {
    bool lo_toque = npc.tile_x == tile_x &&
                    (npc.tile_y == tile_y || npc.tile_y - 1 == tile_y);
    if (lo_toque) {
      posicion = {static_cast<size_t>(npc.tile_x), static_cast<size_t>(npc.tile_y)};
      return true;
    }
  }
  return false;
}

Pueblo::AccionTienda Pueblo::click_tienda(int x, int y) {
  for (int i = 0; i < TIENDA_CANTIDAD_BOTONES; i++) {
    // cppcheck-suppress useStlAlgorithm
    if (botones[i].Contains(x, y)) {
      return static_cast<AccionTienda>(i + 1);
    }
  }
  return NINGUNA;
}

bool Pueblo::hay_tienda_abierta() const {
  return tienda_abierta != TIENDA_CERRADA;
}

void Pueblo::cerrar_tienda() { tienda_abierta = TIENDA_CERRADA; }

void Pueblo::dibujar_tienda(Renderer &renderer, Personaje &personaje) {
  if (tienda_abierta == TIENDA_CERRADA) {
    return;
  }
  int ancho_ventana = renderer.GetOutputWidth();
  int alto_ventana = renderer.GetOutputHeight();

  const SDL2pp::Color oscurecer = COLOR_TIENDA_OSCURECER;
  renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
  renderer.SetDrawColor(oscurecer);
  renderer.FillRect(Rect(0, 0, ancho_ventana, alto_ventana));

  Texture &fondo = fondos_tiendas[tienda_abierta];
  double escala_ancho =
      (ancho_ventana - TIENDA_MARGEN_ANCHO) / double(fondo.GetWidth());
  double escala_alto =
      (alto_ventana - TIENDA_MARGEN_ALTO) / double(fondo.GetHeight());
  double escala = std::min(escala_ancho, escala_alto);
  int ancho = static_cast<int>(fondo.GetWidth() * escala);
  int alto = static_cast<int>(fondo.GetHeight() * escala);
  Rect habitacion((ancho_ventana - ancho) / 2, (alto_ventana - alto) / 2, ancho,
                  alto);
  renderer.Copy(fondo, NullOpt, habitacion);

  int centro_x = ancho_ventana / 2;
  int pie_y = habitacion.y + habitacion.h / 2 + TIENDA_LADO_PERSONAJES;
  dibujar_npc_en(renderer, tienda_abierta, centro_x - TIENDA_LADO_PERSONAJES,
                 pie_y, TIENDA_LADO_PERSONAJES);
  personaje.dibujar_icono(renderer, centro_x + TIENDA_LADO_PERSONAJES, pie_y,
                          TIENDA_LADO_PERSONAJES);

  Texture &titulo = titulos[tienda_abierta];
  renderer.Copy(titulo, NullOpt,
                Rect((ancho_ventana - titulo.GetWidth()) / 2,
                     habitacion.y - titulo.GetHeight() - TIENDA_MARGEN_TITULO,
                     titulo.GetWidth(), titulo.GetHeight()));

  int ancho_total = 0;
  for (Texture &texto : texto_botones) {
    ancho_total += texto.GetWidth() + 2 * TIENDA_RELLENO_BOTON;
  }
  ancho_total += (TIENDA_CANTIDAD_BOTONES - 1) * TIENDA_SEPARACION_BOTONES;

  const SDL2pp::Color fondo_boton = COLOR_BOTON_FONDO;
  const SDL2pp::Color borde_boton = COLOR_BOTON_BORDE;
  int x = (ancho_ventana - ancho_total) / 2;
  int y = alto_ventana - BOTONES_DESDE_ABAJO;
  for (int i = 0; i < TIENDA_CANTIDAD_BOTONES; i++) {
    Texture &texto = texto_botones[i];
    botones[i] = Rect(x, y, texto.GetWidth() + 2 * TIENDA_RELLENO_BOTON,
                      TIENDA_ALTO_BOTON);

    renderer.SetDrawColor(fondo_boton);
    renderer.FillRect(botones[i]);
    renderer.SetDrawColor(borde_boton);
    renderer.DrawRect(botones[i]);
    renderer.Copy(texto, NullOpt,
                  Rect(x + TIENDA_RELLENO_BOTON,
                       y + (TIENDA_ALTO_BOTON - texto.GetHeight()) / 2,
                       texto.GetWidth(), texto.GetHeight()));

    x += botones[i].w + TIENDA_SEPARACION_BOTONES;
  }
}
