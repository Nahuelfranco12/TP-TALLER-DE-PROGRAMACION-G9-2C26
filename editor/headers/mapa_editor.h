#ifndef EDITOR_MAPA_EDITOR_H_
#define EDITOR_MAPA_EDITOR_H_

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

#include "constantes.h"
#include "editor_dtos.h"

struct Dimensiones {
  int ancho = ANCHO_PREDETERMINADO;
  int alto = ALTO_PREDETERMINADO;
};

inline bool dimensionesValidas(const Dimensiones &d) {
  return d.ancho >= DIMENSION_MINIMA && d.ancho <= DIMENSION_MAXIMA &&
         d.alto >= DIMENSION_MINIMA && d.alto <= DIMENSION_MAXIMA;
}

template <typename TipoObjeto>
struct ObjetoColocado {
  TipoObjeto tipo;
  int x;
  int y;
};

template <typename TipoObjeto>
class MapaZona {
 public:
  MapaZona(Dimensiones dimensiones, Terreno pisoBase)
      : dimensiones(dimensiones), pisoBase(pisoBase) {
    if (!dimensionesValidas(dimensiones))
      throw std::invalid_argument("Dimensiones de zona fuera de rango");
    terrenos.assign(cantidadCeldas(dimensiones), pisoBase);
  }

  int ancho() const { return dimensiones.ancho; }
  int alto() const { return dimensiones.alto; }
  Dimensiones tamanio() const { return dimensiones; }

  bool contiene(int x, int y) const {
    return x >= 0 && y >= 0 && x < dimensiones.ancho && y < dimensiones.alto;
  }

  Terreno terrenoEn(int x, int y) const { return terrenos[indice(x, y)]; }

  const std::vector<ObjetoColocado<TipoObjeto>> &objetos() const {
    return objetosColocados;
  }

  void redimensionar(Dimensiones nuevas) {
    if (!dimensionesValidas(nuevas))
      throw std::invalid_argument("Dimensiones de zona fuera de rango");
    std::vector<Terreno> nuevosTerrenos(cantidadCeldas(nuevas), pisoBase);
    for (int y = 0; y < nuevas.alto && y < dimensiones.alto; ++y)
      for (int x = 0; x < nuevas.ancho && x < dimensiones.ancho; ++x)
        nuevosTerrenos[static_cast<std::size_t>(y * nuevas.ancho + x)] =
            terrenos[indice(x, y)];
    terrenos = std::move(nuevosTerrenos);
    dimensiones = nuevas;
    std::erase_if(objetosColocados, [this](const auto &objeto) {
      return !contiene(objeto.x, objeto.y);
    });
  }

 private:
  Dimensiones dimensiones;
  Terreno pisoBase;
  std::vector<Terreno> terrenos;
  std::vector<ObjetoColocado<TipoObjeto>> objetosColocados;

  static std::size_t cantidadCeldas(const Dimensiones &d) {
    return static_cast<std::size_t>(d.ancho * d.alto);
  }

  std::size_t indice(int x, int y) const {
    if (!contiene(x, y))
      throw std::out_of_range("Celda fuera de la zona");
    return static_cast<std::size_t>(y * dimensiones.ancho + x);
  }
};

struct MapaEditor {
  std::string nombre;
  MapaZona<ElementosGranja> granja;
  std::vector<MapaZona<ElementosCaverna>> nivelesCaverna;
  MapaZona<ElementosPueblo> pueblo;
};

MapaEditor crearMapaPredeterminado(Dimensiones granja = {},
                                   Dimensiones caverna = {},
                                   Dimensiones pueblo = {});

#endif  // EDITOR_MAPA_EDITOR_H_
