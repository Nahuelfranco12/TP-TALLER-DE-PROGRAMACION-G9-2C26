#include "interfaz.h"

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

namespace {
const SDL2pp::Color BLANCO = {255, 255, 255, 255};
const int TAMANIO_LETRA = 16;
} // namespace

Interfaz::Interfaz(SDL2pp::Renderer &renderer)
    : fuente("assets/fuentes/DejaVuSans-Bold.ttf", TAMANIO_LETRA),
      texto_musica(renderer, fuente.RenderUTF8_Blended("Música", BLANCO)),
      texto_menos(renderer, fuente.RenderUTF8_Blended("-", BLANCO)),
      texto_mas(renderer, fuente.RenderUTF8_Blended("+", BLANCO)),
      boton_musica(16, 16, 90, 32), boton_menos(114, 16, 32, 32),
      boton_mas(254, 16, 32, 32) {}

bool Interfaz::click(int x, int y, Audio &audio) {
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
}