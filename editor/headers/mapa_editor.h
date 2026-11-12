#ifndef EDITOR_MAPA_EDITOR_H_
#define EDITOR_MAPA_EDITOR_H_

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "constantes.h"
#include "elementos_mapa.h"
//#include "catalogo_elementos.h"

struct Dimensiones {
  int ancho = ANCHO_PREDETERMINADO;
  int alto = ALTO_PREDETERMINADO;
};

inline bool dimensionesValidas(const Dimensiones &d) {
  return d.ancho >= DIMENSION_MINIMA && d.ancho <= DIMENSION_MAXIMA &&
         d.alto >= DIMENSION_MINIMA && d.alto <= DIMENSION_MAXIMA;
}

template <typename TipoObjeto> struct ObjetoColocado {
  TipoObjeto tipo;
  int x;
  int y;
};

struct CeldasOcupadasPorObjeto {
  int ancho;
  int alto;
};

CeldasOcupadasPorObjeto OcupadaPor(ElementosGranja tipo);
CeldasOcupadasPorObjeto OcupadaPor(ElementosCaverna tipo);
CeldasOcupadasPorObjeto OcupadaPor(ElementosPueblo tipo);

bool esUnico(ElementosGranja tipo);
bool esUnico(ElementosCaverna tipo);
bool esUnico(ElementosPueblo tipo);

template <typename TipoObjeto>
bool ocupa(const ObjetoColocado<TipoObjeto> &objeto, int x, int y) {
  CeldasOcupadasPorObjeto celdaOcupada = OcupadaPor(objeto.tipo);
  return x >= objeto.x && x < objeto.x + celdaOcupada.ancho && y >= objeto.y &&
         y < objeto.y + celdaOcupada.alto;
}

template <typename TipoObjeto>
bool seSuperponen(TipoObjeto tipo, int x, int y,
                  const ObjetoColocado<TipoObjeto> &otro) {
  CeldasOcupadasPorObjeto objeto1 = OcupadaPor(tipo);
  CeldasOcupadasPorObjeto objeto2 = OcupadaPor(otro.tipo);
  return x < otro.x + objeto2.ancho && otro.x < x + objeto1.ancho &&
         y < otro.y + objeto2.alto && otro.y < y + objeto1.alto;
}

template <typename TipoObjeto> class MapaZona {
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

  bool existeCelda(int x, int y) const {
    return x >= 0 && y >= 0 && x < dimensiones.ancho && y < dimensiones.alto;
  }

  Terreno terrenoEnCelda(int x, int y) const { return terrenos[indice(x, y)]; }

  void pintarTerrenoConCelda(int x, int y, Terreno terreno) {
    terrenos[indice(x, y)] = terreno;
  }

  const std::vector<ObjetoColocado<TipoObjeto>> &objetos() const {
    return objetosColocados;
  }

  const ObjetoColocado<TipoObjeto> *objetoEnCelda(int x, int y) const {
    auto objeto = std::find_if(
        objetosColocados.begin(), objetosColocados.end(),
        [x, y](const auto &candidato) { return ocupa(candidato, x, y); });
    if (objeto == objetosColocados.end())
      return nullptr;
    return &*objeto;
  }

  bool colocar(TipoObjeto tipo, int x, int y) {
    if (!entra(tipo, x, y))
      return false;
    bool unico = esUnico(tipo);
    bool pisaAOtro =
        std::any_of(objetosColocados.begin(), objetosColocados.end(),
                    [&](const auto &otro) {
                      bool seVaAMover = unico && otro.tipo == tipo;
                      return !seVaAMover && seSuperponen(tipo, x, y, otro);
                    });
    if (pisaAOtro)
      return false;
    if (unico)
      std::erase_if(objetosColocados,
                    [tipo](const auto &objeto) { return objeto.tipo == tipo; });
    objetosColocados.push_back({tipo, x, y});
    return true;
  }

  bool quitarEn(int x, int y) {
    return std::erase_if(objetosColocados, [x, y](const auto &objeto) {
             return ocupa(objeto, x, y);
           }) > 0;
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
      return !entra(objeto.tipo, objeto.x, objeto.y);
    });
  }

private:
  Dimensiones dimensiones;
  Terreno pisoBase;
  std::vector<Terreno> terrenos; // tengo un vector de terrenos
  std::vector<ObjetoColocado<TipoObjeto>> objetosColocados;

  static std::size_t cantidadCeldas(const Dimensiones &d) {
    return static_cast<std::size_t>(d.ancho * d.alto);
  }

  std::size_t indice(int x, int y) const {
    if (!existeCelda(x, y))
      throw std::out_of_range("Celda fuera de la zona");
    return static_cast<std::size_t>(y * dimensiones.ancho + x);
  }

  bool entra(TipoObjeto tipo, int x, int y) const {
    CeldasOcupadasPorObjeto celdaOcupada = OcupadaPor(tipo);
    return existeCelda(x, y) &&
           existeCelda(x + celdaOcupada.ancho - 1, y + celdaOcupada.alto - 1);
  }
};

template <typename TipoObjeto>
void pintarBorde(MapaZona<TipoObjeto> &zona, Terreno terreno) {
  for (int x = 0; x < zona.ancho(); ++x) {
    zona.pintarTerrenoConCelda(x, 0, terreno);
    zona.pintarTerrenoConCelda(x, zona.alto() - 1, terreno);
  }
  for (int y = 0; y < zona.alto(); ++y) {
    zona.pintarTerrenoConCelda(0, y, terreno);
    zona.pintarTerrenoConCelda(zona.ancho() - 1, y, terreno);
  }
}

struct MapaEditor {
  std::string nombre;
  MapaZona<ElementosGranja> granja;
  std::vector<MapaZona<ElementosCaverna>> nivelesCaverna;
  MapaZona<ElementosPueblo> pueblo;
};

MapaEditor crearMapaPredeterminado();

#endif // EDITOR_MAPA_EDITOR_H_
