#include "decoraciones.h"

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace {
const char *ARCHIVOS[] = RUTAS_DECORACIONES;

struct Modelo {
  int archivo;
  SDL_Rect recorte;
  int ancho;
  int alto;
};

// Qué dibujar para cada decoración que manda el servidor
bool modelo_de(TerrainDecorationDto tipo, Modelo &modelo) {
  switch (tipo) {
  // Granja
  case Tree1Dto:
    modelo = {DECO_ARCHIVO_ARBOL1, SPRITE_DECO_ENTERA, DECO_TILES_NORMAL, DECO_TILES_ARBOL_ALTO};
    return true;
  case Tree2Dto:
    modelo = {DECO_ARCHIVO_ARBOL2, SPRITE_DECO_ENTERA, DECO_TILES_NORMAL, DECO_TILES_ARBOL_ALTO};
    return true;
  case TreeRoundedDto:
    modelo = {DECO_ARCHIVO_NATURALEZA, SPRITE_DECO_ARBUSTO_REDONDO, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case TreeBigDto:
    modelo = {DECO_ARCHIVO_NATURALEZA, SPRITE_DECO_ARBUSTO_GRANDE, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case LogDto:
    modelo = {DECO_ARCHIVO_NATURALEZA, SPRITE_DECO_TRONCO_CAIDO, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case StumpDto:
    modelo = {DECO_ARCHIVO_NATURALEZA, SPRITE_DECO_TOCON, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case StoneDto:
    modelo = {DECO_ARCHIVO_PIEDRAS, SPRITE_DECO_PIEDRA, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case StoneGrayDto:
    modelo = {DECO_ARCHIVO_NATURALEZA, SPRITE_DECO_PIEDRA_GRIS, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case StoneGrayBigDto:
    modelo = {DECO_ARCHIVO_NATURALEZA, SPRITE_DECO_PIEDRA_GRIS_GRANDE, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case WaterDecoDto:
    modelo = {DECO_ARCHIVO_NATURALEZA, SPRITE_DECO_AGUA, DECO_TILES_AGUA, DECO_TILES_AGUA};
    return true;
  case MailboxRedDto:
    modelo = {DECO_ARCHIVO_OBJETOS, SPRITE_DECO_BUZON_ROJO, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case BlankSignDto:
    modelo = {DECO_ARCHIVO_OBJETOS, SPRITE_DECO_CARTEL_VACIO, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  // Pueblo
  case MailboxBlueDto:
    modelo = {DECO_ARCHIVO_OBJETOS, SPRITE_DECO_BUZON_AZUL, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case MailBoxGrayDto:
    modelo = {DECO_ARCHIVO_OBJETOS, SPRITE_DECO_BUZON_GRIS, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case LanternOrangeDto:
    modelo = {DECO_ARCHIVO_OBJETOS, SPRITE_DECO_FAROL_NARANJA, DECO_TILES_NORMAL, DECO_TILES_FAROL_ALTO};
    return true;
  case LanternBlueDto:
    modelo = {DECO_ARCHIVO_OBJETOS, SPRITE_DECO_FAROL_AZUL, DECO_TILES_NORMAL, DECO_TILES_FAROL_ALTO};
    return true;
  case BenchDto:
    modelo = {DECO_ARCHIVO_OBJETOS, SPRITE_DECO_BANCO, DECO_TILES_BANCO_ANCHO, DECO_TILES_NORMAL};
    return true;
  // Caverna
  case BarrelDto:
    modelo = {DECO_ARCHIVO_CAVERNA, SPRITE_DECO_BARRIL, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case SkullDecoDto:
    modelo = {DECO_ARCHIVO_CAVERNA, SPRITE_DECO_CALAVERA, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case BoneDto:
    modelo = {DECO_ARCHIVO_CAVERNA, SPRITE_DECO_HUESO, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case RuinsDto:
    modelo = {DECO_ARCHIVO_CAVERNA, SPRITE_DECO_ESCOMBROS, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case TorchDto:
    modelo = {DECO_ARCHIVO_CAVERNA, SPRITE_DECO_ANTORCHA, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case CandleDto:
    modelo = {DECO_ARCHIVO_CAVERNA, SPRITE_DECO_CANDELABRO, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case ShieldDto:
    modelo = {DECO_ARCHIVO_CAVERNA, SPRITE_DECO_ESCUDO, DECO_TILES_NORMAL, DECO_TILES_NORMAL};
    return true;
  case PitDto:
    modelo = {DECO_ARCHIVO_POZO, SPRITE_DECO_POZO, DECO_TILES_POZO, DECO_TILES_POZO};
    return true;
  default:
    return false;
  }
}
} // namespace

Decoraciones::Decoraciones(Renderer &renderer) {
  for (const char *archivo : ARCHIVOS) {
    // cppcheck-suppress useStlAlgorithm
    imagenes.emplace_back(renderer, archivo);
  }
}

void Decoraciones::dibujar(Renderer &renderer,
                           const std::vector<Decoracion> &decoraciones,
                           int camara_x, int camara_y, int lado) {
  for (const Decoracion &decoracion : decoraciones) {
    Modelo modelo{};
    if (!modelo_de(decoracion.tipo, modelo)) {
      continue;
    }
    Rect destino(decoracion.tile_x * lado - camara_x,
                 decoracion.tile_y * lado - camara_y, modelo.ancho * lado,
                 modelo.alto * lado);
    SDL2pp::Texture &imagen = imagenes[modelo.archivo];
    if (modelo.recorte.w == 0) {
      renderer.Copy(imagen, NullOpt, destino);
    } else {
      renderer.Copy(imagen, Rect(modelo.recorte), destino);
    }
  }
}