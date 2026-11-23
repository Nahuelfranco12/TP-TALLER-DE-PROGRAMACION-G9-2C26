#include "interfaz.h"

#include <string>

#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {
const SDL2pp::Color BLANCO = COLOR_TEXTO;

std::string dos_digitos(size_t numero) {
  if (numero < RELOJ_MINIMO_DOS_CIFRAS) {
    return TEXTO_JUEGO_CERO + std::to_string(numero);
  }
  return std::to_string(numero);
}
} // namespace

Interfaz::Interfaz(SDL2pp::Renderer &renderer,
                   const std::string &codigo_partida)
    : fuente(RUTA_FUENTE_JUEGO, HUD_TAMANIO_LETRA),
      texto_musica(renderer,
                   fuente.RenderUTF8_Blended(TEXTO_JUEGO_MUSICA, BLANCO)),
      texto_menos(renderer,
                  fuente.RenderUTF8_Blended(TEXTO_JUEGO_MENOS, BLANCO)),
      texto_mas(renderer, fuente.RenderUTF8_Blended(TEXTO_JUEGO_MAS, BLANCO)),
      boton_musica(HUD_MARGEN, HUD_MARGEN, HUD_ANCHO_BOTON_MUSICA,
                   HUD_ALTO_BOTON),
      boton_menos(HUD_BOTON_MENOS_X, HUD_MARGEN, HUD_ALTO_BOTON,
                  HUD_ALTO_BOTON),
      boton_mas(HUD_BOTON_MAS_X, HUD_MARGEN, HUD_ALTO_BOTON, HUD_ALTO_BOTON),
      codigo(codigo_partida),
      texto_boton_codigo(renderer, fuente.RenderUTF8_Blended(
                                       TEXTO_JUEGO_BOTON_CODIGO, BLANCO)),
      texto_codigo(renderer, fuente.RenderUTF8_Blended(TEXTO_JUEGO_CODIGO +
                                                           codigo_partida +
                                                           TEXTO_JUEGO_COPIADO,
                                                       BLANCO)),
      textura_tiempo(renderer, fuente.RenderUTF8_Blended(
                                   TEXTO_JUEGO_TIEMPO_INICIAL, BLANCO)),
      textura_monedas(renderer, fuente.RenderUTF8_Blended(
                                    TEXTO_JUEGO_MONEDAS_INICIAL, BLANCO)),
      texto_regalo(renderer,
                   fuente.RenderUTF8_Blended(TEXTO_JUEGO_REGALO, BLANCO)),
      texto_aceptar(renderer,
                    fuente.RenderUTF8_Blended(TEXTO_JUEGO_ACEPTAR, BLANCO)),
      texto_rechazar(renderer,
                     fuente.RenderUTF8_Blended(TEXTO_JUEGO_RECHAZAR, BLANCO)) {}

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
  const SDL2pp::Color fondo = COLOR_BOTON_FONDO;
  const SDL2pp::Color borde = COLOR_BOTON_BORDE;
  renderer.SetDrawColor(fondo);
  renderer.FillRect(boton);
  renderer.SetDrawColor(borde);
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

  const SDL2pp::Color encendida = COLOR_RAYITA_ENCENDIDA;
  const SDL2pp::Color apagada = COLOR_RAYITA_APAGADA;
  int endendidas = audio.obtener_volumen_musica() / AUDIO_INCREMENTO_VOLUMEN;
  for (int i = 0; i < HUD_RAYITAS_VOLUMEN; i++) {
    Rect rayita(HUD_RAYITA_X + i * HUD_RAYITA_PASO, HUD_RAYITA_Y,
                HUD_RAYITA_ANCHO, HUD_RAYITA_ALTO);
    if (i < endendidas) {
      renderer.SetDrawColor(encendida);
    } else {
      renderer.SetDrawColor(apagada);
    }
    renderer.FillRect(rayita);
  }
  SDL2pp::Texture *texto = &texto_boton_codigo;
  if (mostrando_codigo) {
    texto = &texto_codigo;
  }
  int ancho = texto->GetWidth() + 2 * HUD_RELLENO;
  boton_codigo = Rect(renderer.GetOutputWidth() - ancho - HUD_MARGEN,
                      HUD_MARGEN, ancho, HUD_ALTO_BOTON);
  dibujar_boton(renderer, boton_codigo, *texto);

  int alto_fila = HUD_ALTO_BOTON + HUD_SEPARACION_CAJAS;

  int ancho_tiempo = textura_tiempo.GetWidth() + 2 * HUD_RELLENO;
  Rect caja_tiempo(renderer.GetOutputWidth() - ancho_tiempo - HUD_MARGEN,
                   HUD_MARGEN + alto_fila, ancho_tiempo, HUD_ALTO_BOTON);
  dibujar_boton(renderer, caja_tiempo, textura_tiempo);

  int ancho_monedas = textura_monedas.GetWidth() + 2 * HUD_RELLENO;
  Rect caja_monedas(renderer.GetOutputWidth() - ancho_monedas - HUD_MARGEN,
                    HUD_MARGEN + 2 * alto_fila, ancho_monedas, HUD_ALTO_BOTON);
  dibujar_boton(renderer, caja_monedas, textura_monedas);
}

void Interfaz::actualizar_tiempo(Renderer &renderer, const GameTimeDto &tiempo,
                                 size_t dia) {
  hora = tiempo.hours;
  minutos = tiempo.minutes;

  std::string nuevo = TEXTO_JUEGO_DIA + std::to_string(dia) +
                      TEXTO_JUEGO_SEPARADOR_DIA + dos_digitos(hora) +
                      TEXTO_JUEGO_SEPARADOR_HORA + dos_digitos(minutos);
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
  std::string texto = TEXTO_JUEGO_MONEDAS + std::to_string(monedas);
  textura_monedas =
      SDL2pp::Texture(renderer, fuente.RenderUTF8_Blended(texto, BLANCO));
}

void Interfaz::dibujar_noche(Renderer &renderer) const {
  int minutos_del_dia =
      static_cast<int>(hora) * MINUTOS_POR_HORA + static_cast<int>(minutos);
  int inicio = NOCHE_HORA_ATARDECER * MINUTOS_POR_HORA;
  int fin = NOCHE_HORA_OSCURA * MINUTOS_POR_HORA;

  int alfa = 0;
  if (hora < DIA_HORA_INICIO || minutos_del_dia >= fin) {
    alfa = NOCHE_OSCURIDAD_MAXIMA;
  } else if (minutos_del_dia > inicio) {
    alfa = NOCHE_OSCURIDAD_MAXIMA * (minutos_del_dia - inicio) / (fin - inicio);
  }
  if (alfa == 0) {
    return;
  }

  const SDL2pp::Color noche = COLOR_NOCHE;
  renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
  renderer.SetDrawColor(noche.r, noche.g, noche.b, alfa);
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
  caja_regalo = Rect((renderer.GetOutputWidth() - REGALO_ANCHO) / 2,
                     (renderer.GetOutputHeight() - REGALO_ALTO) / 2,
                     REGALO_ANCHO, REGALO_ALTO);
  const SDL2pp::Color fondo = COLOR_CAJA_REGALO;
  const SDL2pp::Color borde = COLOR_BOTON_BORDE;
  renderer.SetDrawColor(fondo);
  renderer.FillRect(caja_regalo);
  renderer.SetDrawColor(borde);
  renderer.DrawRect(caja_regalo);

  Rect lugar_titulo(caja_regalo.x +
                        (REGALO_ANCHO - texto_regalo.GetWidth()) / 2,
                    caja_regalo.y + REGALO_MARGEN_TITULO,
                    texto_regalo.GetWidth(), texto_regalo.GetHeight());
  renderer.Copy(texto_regalo, NullOpt, lugar_titulo);

  icono_regalo =
      Rect(caja_regalo.x + (REGALO_ANCHO - INVENTARIO_LADO_CASILLERO) / 2,
           caja_regalo.y + REGALO_ICONO_Y, INVENTARIO_LADO_CASILLERO,
           INVENTARIO_LADO_CASILLERO);

  int botones_y = caja_regalo.y + REGALO_ALTO - REGALO_BOTONES_DESDE_ABAJO;
  boton_aceptar = Rect(caja_regalo.x + REGALO_MARGEN_BOTONES, botones_y,
                       REGALO_ANCHO_BOTON, HUD_ALTO_BOTON);
  boton_rechazar = Rect(caja_regalo.x + REGALO_ANCHO - REGALO_ANCHO_BOTON -
                            REGALO_MARGEN_BOTONES,
                        botones_y, REGALO_ANCHO_BOTON, HUD_ALTO_BOTON);

  dibujar_boton(renderer, boton_aceptar, texto_aceptar);
  dibujar_boton(renderer, boton_rechazar, texto_rechazar);
}
