#include "interfaz.h"

#include <string>

#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {
const SDL2pp::Color BLANCO = {255, 255, 255, 255};
const int TAMANIO_LETRA = 16;
const int MARGEN = 16;
const int ALTO_BOTON = 32;
const int RELLENO = 8;
const int HORA_ATARDECER = 18;
const int HORA_NOCHE = 22;
const int OSCURIDAD_MAXIMA = 170;

std::string dos_digitos(size_t numero) {
  if (numero < 10) {
    return "0" + std::to_string(numero);
  }
  return std::to_string(numero);
}
} // namespace

Interfaz::Interfaz(SDL2pp::Renderer &renderer,
                   const std::string &codigo_partida)
    : fuente("assets/fuentes/DejaVuSans-Bold.ttf", TAMANIO_LETRA),
      texto_musica(renderer, fuente.RenderUTF8_Blended("Música", BLANCO)),
      texto_menos(renderer, fuente.RenderUTF8_Blended("-", BLANCO)),
      texto_mas(renderer, fuente.RenderUTF8_Blended("+", BLANCO)),
      boton_musica(16, 16, 90, 32), boton_menos(114, 16, 32, 32),
      boton_mas(254, 16, 32, 32), codigo(codigo_partida),
      texto_boton_codigo(
          renderer, fuente.RenderUTF8_Blended("Código Multiplayer", BLANCO)),
      texto_codigo(renderer,
                   fuente.RenderUTF8_Blended(
                       "Código: " + codigo_partida + "  (copiado)", BLANCO)),
      textura_tiempo(renderer,
                     fuente.RenderUTF8_Blended("Día 1 06:00", BLANCO)),
      textura_monedas(renderer,
                      fuente.RenderUTF8_Blended("Monedas: 0", BLANCO)),
      texto_regalo(renderer,
                   fuente.RenderUTF8_Blended("¡Te ofrecen un regalo!", BLANCO)),
      texto_aceptar(renderer, fuente.RenderUTF8_Blended("Aceptar", BLANCO)),
      texto_rechazar(renderer, fuente.RenderUTF8_Blended("Rechazar", BLANCO)) {}

bool Interfaz::click(int x, int y, Audio &audio) {
  if (boton_codigo.Contains(x, y)) {
    mostrando_codigo = !mostrando_codigo;
    if (mostrando_codigo)
      SDL_SetClipboardText(codigo.c_str());
    return true;
  }
  if (boton_musica.Contains(x, y)) {
    audio.cambiar_musica();
    return true;
  } else if (boton_menos.Contains(x, y)) {
    audio.bajar_volumen_musica();
    return true;
  } else if (boton_mas.Contains(x, y)) {
    audio.subir_volumen_musica();
    return true;
  }
  return false;
}

void Interfaz::dibujar_boton(SDL2pp::Renderer &renderer,
                             const SDL2pp::Rect &boton,
                             SDL2pp::Texture &texto) {
  renderer.SetDrawColor(30, 30, 30, 255);
  renderer.FillRect(boton);
  renderer.SetDrawColor(230, 230, 230, 255);
  renderer.DrawRect(boton);

  int ancho = texto.GetWidth();
  int alto = texto.GetHeight();
  SDL2pp::Rect destino(boton.x + (boton.w - ancho) / 2,
                       boton.y + (boton.h - alto) / 2, ancho, alto);
  renderer.Copy(texto, NullOpt, destino);
}

void Interfaz::dibujar(SDL2pp::Renderer &renderer, const Audio &audio) {
  dibujar_boton(renderer, boton_musica, texto_musica);
  dibujar_boton(renderer, boton_menos, texto_menos);
  dibujar_boton(renderer, boton_mas, texto_mas);

  int endendidas = audio.obtener_volumen_musica() / 16;
  for (int i = 0; i < 8; i++) {
    Rect rayita(152 + i * 12, 22, 8, 20);
    if (i < endendidas) {
      renderer.SetDrawColor(230, 190, 190, 255);
    } else {
      renderer.SetDrawColor(80, 80, 80, 255);
    }
    renderer.FillRect(rayita);
  }
  SDL2pp::Texture *texto = &texto_boton_codigo;
  if (mostrando_codigo) {
    texto = &texto_codigo;
  }
  int ancho = texto->GetWidth() + 2 * RELLENO;
  boton_codigo = Rect(renderer.GetOutputWidth() - ancho - MARGEN, MARGEN, ancho,
                      ALTO_BOTON);
  dibujar_boton(renderer, boton_codigo, *texto);

  int ancho_tiempo = textura_tiempo.GetWidth() + 2 * RELLENO;
  Rect caja_tiempo(renderer.GetOutputWidth() - ancho_tiempo - MARGEN,
                   MARGEN + ALTO_BOTON + 8, ancho_tiempo, ALTO_BOTON);
  dibujar_boton(renderer, caja_tiempo, textura_tiempo);

  int ancho_monedas = textura_monedas.GetWidth() + 2 * RELLENO;
  Rect caja_monedas(renderer.GetOutputWidth() - ancho_monedas - MARGEN,
                    MARGEN + 2 * (ALTO_BOTON + 8), ancho_monedas, ALTO_BOTON);
  dibujar_boton(renderer, caja_monedas, textura_monedas);
}

void Interfaz::actualizar_tiempo(Renderer &renderer, const GameTimeDto &tiempo,
                                 size_t dia) {
  hora = tiempo.hours;
  minutos = tiempo.minutes;

  std::string nuevo = "Día " + std::to_string(dia) + " " + dos_digitos(hora) +
                      ":" + dos_digitos(minutos);
  if (nuevo != texto_tiempo) {
    texto_tiempo = nuevo;
    textura_tiempo =
        SDL2pp::Texture(renderer, fuente.RenderUTF8_Blended(nuevo, BLANCO));
  }
}

void Interfaz::actualizar_monedas(Renderer &renderer, size_t nuevas_monedas) {
  if (nuevas_monedas == monedas) {
    return;
  }
  monedas = nuevas_monedas;
  std::string texto = "Monedas: " + std::to_string(monedas);
  textura_monedas =
      SDL2pp::Texture(renderer, fuente.RenderUTF8_Blended(texto, BLANCO));
}

void Interfaz::dibujar_noche(Renderer &renderer) const {
  int minutos_del_dia = static_cast<int>(hora) * 60 + static_cast<int>(minutos);
  int inicio = HORA_ATARDECER * 60;
  int fin = HORA_NOCHE * 60;

  int alfa = 0;
  if (hora < 6 || minutos_del_dia >= fin) {
    alfa = OSCURIDAD_MAXIMA;
  } else if (minutos_del_dia > inicio) {
    alfa = OSCURIDAD_MAXIMA * (minutos_del_dia - inicio) / (fin - inicio);
  }
  if (alfa == 0) {
    return;
  }

  renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
  renderer.SetDrawColor(10, 10, 40, alfa);
  renderer.FillRect(
      Rect(0, 0, renderer.GetOutputWidth(), renderer.GetOutputHeight()));
}

void Interfaz::actualizar_regalo(const PendingGiftDto &pendiente) {
  hay_regalo = pendiente.gift.count > 0;
  regalo = pendiente.gift;
}

bool Interfaz::hay_regalo_pendiente() const { return hay_regalo; }

const InventorySlotDto &Interfaz::regalo_pendiente() const { return regalo; }

Rect Interfaz::lugar_icono_regalo() const { return icono_regalo; }

void Interfaz::cerrar_regalo() { hay_regalo = false; }

bool Interfaz::click_regalo(int x, int y, bool &acepto) {
  if (!hay_regalo) {
    return false;
  }
  if (boton_aceptar.Contains(x, y)) {
    acepto = true;
  } else if (boton_rechazar.Contains(x, y)) {
    acepto = false;
  } else {
    return false;
  }
  cerrar_regalo();
  return true;
}

void Interfaz::dibujar_regalo(Renderer &renderer) {
  const int ANCHO = 280;
  const int ALTO = 140;
  caja_regalo = Rect((renderer.GetOutputWidth() - ANCHO) / 2,
                     (renderer.GetOutputHeight() - ALTO) / 2, ANCHO, ALTO);
  renderer.SetDrawColor(40, 30, 20, 240);
  renderer.FillRect(caja_regalo);
  renderer.SetDrawColor(230, 230, 230, 255);
  renderer.DrawRect(caja_regalo);

  renderer.Copy(texto_regalo, NullOpt,
                Rect(caja_regalo.x + (ANCHO - texto_regalo.GetWidth()) / 2,
                     caja_regalo.y + 10, texto_regalo.GetWidth(),
                     texto_regalo.GetHeight()));

  icono_regalo =
      Rect(caja_regalo.x + (ANCHO - 44) / 2, caja_regalo.y + 40, 44, 44);

  boton_aceptar =
      Rect(caja_regalo.x + 20, caja_regalo.y + ALTO - 44, 110, ALTO_BOTON);
  boton_rechazar = Rect(caja_regalo.x + ANCHO - 130, caja_regalo.y + ALTO - 44,
                        110, ALTO_BOTON);

  dibujar_boton(renderer, boton_aceptar, texto_aceptar);
  dibujar_boton(renderer, boton_rechazar, texto_rechazar);
}
