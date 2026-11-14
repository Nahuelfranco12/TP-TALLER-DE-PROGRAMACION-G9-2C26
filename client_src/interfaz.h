#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <SDL2pp/SDL2pp.hh>
#include <string>

#include "audio.h"
#include "common_src/game_dtos.h"

class Interfaz {
private:
  SDL2pp::Font fuente;

  SDL2pp::Texture texto_musica;
  SDL2pp::Texture texto_menos;
  SDL2pp::Texture texto_mas;

  SDL2pp::Rect boton_musica;
  SDL2pp::Rect boton_menos;
  SDL2pp::Rect boton_mas;
  std::string codigo;
  SDL2pp::Texture texto_boton_codigo;
  SDL2pp::Texture texto_codigo;
  SDL2pp::Rect boton_codigo;
  bool mostrando_codigo = false;

  size_t hora = 6;
  size_t minutos = 0;
  std::string texto_tiempo;
  SDL2pp::Texture textura_tiempo;

  size_t monedas = 0;
  SDL2pp::Texture textura_monedas;

  bool hay_regalo = false;
  InventorySlotDto regalo;
  SDL2pp::Texture texto_regalo;
  SDL2pp::Texture texto_aceptar;
  SDL2pp::Texture texto_rechazar;
  SDL2pp::Rect caja_regalo;
  SDL2pp::Rect icono_regalo;
  SDL2pp::Rect boton_aceptar;
  SDL2pp::Rect boton_rechazar;

  static void dibujar_boton(SDL2pp::Renderer &renderer,
                            const SDL2pp::Rect &boton, SDL2pp::Texture &texto);

public:
  Interfaz(SDL2pp::Renderer &renderer, const std::string &codigo_partida);

  bool click(int x, int y, Audio &audio);

  void dibujar(SDL2pp::Renderer &renderer, const Audio &audio);

  void actualizar_tiempo(SDL2pp::Renderer &renderer, const GameTimeDto &tiempo, size_t dia);

  void dibujar_noche(SDL2pp::Renderer &renderer) const;

  void actualizar_regalo(const PendingGiftDto &pendiente);
  bool hay_regalo_pendiente() const;
  const InventorySlotDto &regalo_pendiente() const;
  SDL2pp::Rect lugar_icono_regalo() const;
  void cerrar_regalo();

  bool click_regalo(int x, int y, bool &acepto);

  void dibujar_regalo(SDL2pp::Renderer &renderer);

  void actualizar_monedas(SDL2pp::Renderer &renderer, size_t nuevas_monedas);
};
#endif
