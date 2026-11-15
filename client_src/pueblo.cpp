#include "pueblo.h"
#include "personaje.h"

#include <algorithm>

#include <SDL2/SDL.h>

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;

namespace {
const int ESCALA = 4;
const int TILE = 16 * ESCALA;

const SDL_Rect MODELOS_PUESTOS[4] = {
    {240, 176, 112, 144}, // Pierre's
    {80, 320, 144, 128},  // Clint
    {192, 640, 192, 160}, // Robin
    {256, 0, 144, 176},   // Marnie
};

struct ModeloNpc {
  const char *archivo;
  int lado_cuadro;
  int pie_y;
};

const ModeloNpc MODELOS_NPCS[4] = {
    {"assets/npcs/pierre.png", 32, 32},
    {"assets/npcs/clint.png", 32, 32},
    {"assets/npcs/robin.png", 64, 48},
    {"assets/npcs/marnie.png", 64, 48},
};

const int CUADROS_NPC = 4;
const long VUELTAS_POR_CUADRO_NPC = 12;

const SDL2pp::Color BLANCO(255, 255, 255, 255);

const char *TITULOS[4] = {
    "Tienda de Pierre",
    "Herrería de Clint",
    "Carpintería de Robin",
    "Rancho de Marnie",
};

const char *FONDOS_TIENDAS[4] = {
    "assets/tiendas/pierre.png",
    "assets/tiendas/clint.jpeg",
    "assets/tiendas/robin.jpg",
    "assets/tiendas/marnie.jpg",
};

const char *TEXTOS_BOTONES[4] = {"Comprar", "Vender", "Hablar", "Salir"};

const int ALTO_BOTON = 36;
const int SEPARACION_BOTONES = 12;
const int LADO_PERSONAJES = 48; // tamaño de un tile para el NPC y el jugador

int tile_de_pixel(int pixel) {
  int tile = pixel / TILE;
  if (pixel < 0 && pixel % TILE != 0) {
    tile--;
  }
  return tile;
}
} // namespace

Pueblo::Pueblo(Renderer &renderer)
    : edificios(renderer, "assets/edificios/PelicanTown_Buildings.png"),
      fuente("assets/fuentes/DejaVuSans-Bold.ttf", 20), vueltas(0),
      tienda_abierta(-1) {

  lista_puestos.push_back({10, 20, 0});
  lista_puestos.push_back({30, 36, 1});
  lista_puestos.push_back({29, 3, 2});
  lista_puestos.push_back({52, 18, 3});

  for (const ModeloNpc &modelo : MODELOS_NPCS) {
    sprites_npcs.emplace_back(renderer, modelo.archivo);
  }

  lista_npcs.push_back({15, 29, 0});
  lista_npcs.push_back({34, 44, 1});
  lista_npcs.push_back({37, 13, 2});
  lista_npcs.push_back({57, 29, 3});

  for (const char *titulo : TITULOS) {
    titulos.emplace_back(renderer, fuente.RenderUTF8_Blended(titulo, BLANCO));
  }
  for (const char *texto : TEXTOS_BOTONES) {
    texto_botones.emplace_back(renderer,
                               fuente.RenderUTF8_Blended(texto, BLANCO));
  }
  botones.resize(4);
  for (const char *archivo : FONDOS_TIENDAS) {
    fondos_tiendas.emplace_back(renderer, archivo);
  }
}

void Pueblo::animar(long vueltas_pasadas) { vueltas += vueltas_pasadas; }

void Pueblo::dibujar_puesto(SDL2pp::Renderer &renderer, const Puesto &puesto,
                            int camara_x, int camara_y, int lado) {
  const SDL_Rect &modelo = MODELOS_PUESTOS[puesto.modelo];
  Rect origen(modelo.x, modelo.y, modelo.w, modelo.h);

  int x = puesto.tile_x * lado - camara_x;
  int y = puesto.tile_y * lado - camara_y;
  Rect destino(x, y, modelo.w * lado / 16, modelo.h * lado / 16);
  renderer.Copy(edificios, origen, destino);
}

void Pueblo::dibujar_npc_en(Renderer &renderer, int modelo, int centro_x,
                            int pie_y, int lado) {
  const ModeloNpc &datos = MODELOS_NPCS[modelo];

  int cuadro =
      static_cast<int>((vueltas / VUELTAS_POR_CUADRO_NPC) % CUADROS_NPC);
  Rect origen(cuadro * datos.lado_cuadro, 0, datos.lado_cuadro,
              datos.lado_cuadro);

  int tamanio = datos.lado_cuadro * lado / 16;
  int pie = datos.pie_y * lado / 16;
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
  for (const Puesto &puesto : lista_puestos) {
    dibujar_puesto(renderer, puesto, camara_x, camara_y, lado);
  }
  for (const Npc &npc : lista_npcs) {
    dibujar_npc(renderer, npc, camara_x, camara_y, lado);
  }
}

void Pueblo::actualizar(const std::map<GamePositionDto, EntityDto> &) {
  // hasta que mande el servidor
}

bool Pueblo::click_npc(int x, int y, int camara_x, int camara_y) {
  int tile_x = tile_de_pixel(x + camara_x);
  int tile_y = tile_de_pixel(y + camara_y);

  for (const Npc &npc : lista_npcs) {
    bool lo_toque = npc.tile_x == tile_x &&
                    (npc.tile_y == tile_y || npc.tile_y - 1 == tile_y);
    if (lo_toque) {
      tienda_abierta = npc.modelo;
      return true;
    }
  }
  return false;
}

Pueblo::AccionTienda Pueblo::click_tienda(int x, int y) {
  for (int i = 0; i < 4; i++) {
    if (botones[i].Contains(x, y)) {
      return static_cast<AccionTienda>(i + 1);
    }
  }
  return NINGUNA;
}

bool Pueblo::hay_tienda_abierta() const { return tienda_abierta >= 0; }

void Pueblo::cerrar_tienda() { tienda_abierta = -1; }

void Pueblo::dibujar_tienda(Renderer &renderer, Personaje &personaje) {
  if (tienda_abierta < 0) {
    return;
  }
  int ancho_ventana = renderer.GetOutputWidth();
  int alto_ventana = renderer.GetOutputHeight();

  renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
  renderer.SetDrawColor(0, 0, 0, 200);
  renderer.FillRect(Rect(0, 0, ancho_ventana, alto_ventana));

  Texture &fondo = fondos_tiendas[tienda_abierta];
  double escala = std::min((ancho_ventana - 40) / double(fondo.GetWidth()),
                           (alto_ventana - 140) / double(fondo.GetHeight()));
  int ancho = static_cast<int>(fondo.GetWidth() * escala);
  int alto = static_cast<int>(fondo.GetHeight() * escala);
  Rect habitacion((ancho_ventana - ancho) / 2, (alto_ventana - alto) / 2, ancho,
                  alto);
  renderer.Copy(fondo, NullOpt, habitacion);

  int centro_x = ancho_ventana / 2;
  int pie_y = habitacion.y + habitacion.h / 2 + LADO_PERSONAJES;
  dibujar_npc_en(renderer, tienda_abierta, centro_x - LADO_PERSONAJES, pie_y,
                 LADO_PERSONAJES);
  personaje.dibujar_icono(renderer, centro_x + LADO_PERSONAJES, pie_y,
                          LADO_PERSONAJES);

  Texture &titulo = titulos[tienda_abierta];
  renderer.Copy(titulo, NullOpt,
                Rect((ancho_ventana - titulo.GetWidth()) / 2,
                     habitacion.y - titulo.GetHeight() - 10, titulo.GetWidth(),
                     titulo.GetHeight()));

  int ancho_total = 0;
  for (Texture &texto : texto_botones) {
    ancho_total += texto.GetWidth() + 24;
  }
  ancho_total += 3 * SEPARACION_BOTONES;

  int x = (ancho_ventana - ancho_total) / 2;
  int y = habitacion.y + habitacion.h + 10;
  for (int i = 0; i < 4; i++) {
    Texture &texto = texto_botones[i];
    botones[i] = Rect(x, y, texto.GetWidth() + 24, ALTO_BOTON);

    renderer.SetDrawColor(30, 30, 30, 255);
    renderer.FillRect(botones[i]);
    renderer.SetDrawColor(230, 230, 230, 255);
    renderer.DrawRect(botones[i]);
    renderer.Copy(texto, NullOpt,
                  Rect(x + 12, y + (ALTO_BOTON - texto.GetHeight()) / 2,
                       texto.GetWidth(), texto.GetHeight()));

    x += botones[i].w + SEPARACION_BOTONES;
  }
}