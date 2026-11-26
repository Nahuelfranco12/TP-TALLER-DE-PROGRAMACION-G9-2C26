#ifndef EDITOR_MAPA_EDITOR_H_
#define EDITOR_MAPA_EDITOR_H_

#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "constantes_mapa.h"
#include "elementos_mapa.h"

struct Dimensiones {
  int ancho = ANCHO_PREDETERMINADO;
  int alto = ALTO_PREDETERMINADO;
};

inline bool sonDimensionesValidas(const Dimensiones &d) {
  return d.ancho >= DIMENSION_MINIMA && d.ancho <= DIMENSION_MAXIMA &&
         d.alto >= DIMENSION_MINIMA && d.alto <= DIMENSION_MAXIMA;
}

template <typename TipoObjeto> struct ObjetoColocado {
  TipoObjeto tipo;
  int x;
  int y;
};

struct TamanioEnCeldas {
  int ancho;
  int alto;
};

TamanioEnCeldas tamanioEnCeldasDe(ElementosGranja tipo);
TamanioEnCeldas tamanioEnCeldasDe(ElementosCaverna tipo);
TamanioEnCeldas tamanioEnCeldasDe(ElementosPueblo tipo);

bool esUnicoEnZona(ElementosGranja tipo);
bool esUnicoEnZona(ElementosCaverna tipo);
bool esUnicoEnZona(ElementosPueblo tipo);
bool esCabania(ElementosGranja tipo);

template <typename TipoObjeto>
bool objetoOcupaCelda(const ObjetoColocado<TipoObjeto> &objeto, int x, int y) {
  TamanioEnCeldas celdaOcupada = tamanioEnCeldasDe(objeto.tipo);
  return x >= objeto.x && x < objeto.x + celdaOcupada.ancho && y >= objeto.y &&
         y < objeto.y + celdaOcupada.alto;
}

template <typename TipoObjeto>
bool seSuperponeConOtro(TipoObjeto tipo, int x, int y,
                        const ObjetoColocado<TipoObjeto> &otro) {
  TamanioEnCeldas objeto1 = tamanioEnCeldasDe(tipo);
  TamanioEnCeldas objeto2 = tamanioEnCeldasDe(otro.tipo);
  return x < otro.x + objeto2.ancho && otro.x < x + objeto1.ancho &&
         y < otro.y + objeto2.alto && otro.y < y + objeto1.alto;
}

template <typename TipoObjeto> class MapaZona {
public:
  MapaZona(Dimensiones dimensiones, Terreno pisoBase)
      : dimensiones(dimensiones), pisoBase(pisoBase) {
    if (!sonDimensionesValidas(dimensiones))
      throw std::invalid_argument(TEXTO_ERROR_DIMENSIONES_ZONA);
    terrenos.assign(cantidadCeldas(dimensiones), pisoBase);
  }

  int ancho() const { return dimensiones.ancho; }
  int alto() const { return dimensiones.alto; }
  Dimensiones tamanio() const { return dimensiones; }

  bool existeCelda(int x, int y) const {
    return x >= 0 && y >= 0 && x < dimensiones.ancho && y < dimensiones.alto;
  }

  Terreno terrenoEnCelda(int x, int y) const {
    return terrenos[indiceDeCelda(x, y)];
  }

  void pintarCelda(int x, int y, Terreno terreno) {
    terrenos[indiceDeCelda(x, y)] = terreno;
  }

  const std::vector<ObjetoColocado<TipoObjeto>> &objetos() const {
    return objetosColocados;
  }

  bool colocarObjetoEnCelda(TipoObjeto tipo, int x, int y) {
    if (!entraEnLaZona(tipo, x, y))
      return false;
    bool unico = esUnicoEnZona(tipo);
    if (pisaAOtroObjeto(tipo, x, y, unico))
      return false;
    if (unico)
      std::erase_if(objetosColocados,
                    [tipo](const auto &objeto) { return objeto.tipo == tipo; });
    objetosColocados.push_back({tipo, x, y});
    return true;
  }

  bool quitarObjetoEnCelda(int x, int y) {
    return std::erase_if(objetosColocados, [x, y](const auto &objeto) {
             return objetoOcupaCelda(objeto, x, y);
           }) > 0;
  }

  void redimensionarZona(Dimensiones nuevas) {
    if (!sonDimensionesValidas(nuevas))
      throw std::invalid_argument(TEXTO_ERROR_DIMENSIONES_ZONA);
    std::vector<Terreno> nuevosTerrenos(cantidadCeldas(nuevas), pisoBase);
    for (int y = 0; y < nuevas.alto && y < dimensiones.alto; ++y)
      for (int x = 0; x < nuevas.ancho && x < dimensiones.ancho; ++x)
        nuevosTerrenos[static_cast<std::size_t>(y * nuevas.ancho + x)] =
            terrenos[indiceDeCelda(x, y)];
    terrenos = std::move(nuevosTerrenos);
    dimensiones = nuevas;
    std::erase_if(objetosColocados, [this](const auto &objeto) {
      return !entraEnLaZona(objeto.tipo, objeto.x, objeto.y);
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

  std::size_t indiceDeCelda(int x, int y) const {
    if (!existeCelda(x, y))
      throw std::out_of_range(TEXTO_ERROR_CELDA_FUERA_DE_ZONA);
    return static_cast<std::size_t>(y * dimensiones.ancho + x);
  }

  bool entraEnLaZona(TipoObjeto tipo, int x, int y) const {
    TamanioEnCeldas celdaOcupada = tamanioEnCeldasDe(tipo);
    return existeCelda(x, y) &&
           existeCelda(x + celdaOcupada.ancho - 1, y + celdaOcupada.alto - 1);
  }

bool pisaAOtroObjeto(TipoObjeto tipo, int x, int y, bool unico) const {
	for (const ObjetoColocado<TipoObjeto> &otro : objetosColocados) {
      bool seVaAMover = unico && otro.tipo == tipo;
      if (!seVaAMover && seSuperponeConOtro(tipo, x, y, otro))
        return true;
    }
    return false;
}
};

template <typename TipoObjeto>
void pintarBordeDeZona(MapaZona<TipoObjeto> &zona, Terreno terreno) {
  for (int x = 0; x < zona.ancho(); ++x) {
    zona.pintarCelda(x, 0, terreno);
    zona.pintarCelda(x, zona.alto() - 1, terreno);
  }
  for (int y = 0; y < zona.alto(); ++y) {
    zona.pintarCelda(0, y, terreno);
    zona.pintarCelda(zona.ancho() - 1, y, terreno);
  }
}

Terreno terrenoBaseDeZona(Zona zona);

MapaZona<ElementosCaverna> crearNivelCavernaConParedes(Dimensiones dimensiones);

struct MapaEditor {
  std::string nombre;
  MapaZona<ElementosGranja> granja;
  std::vector<MapaZona<ElementosCaverna>> nivelesCaverna;
  MapaZona<ElementosPueblo> pueblo;
};

MapaEditor crearMapaVacio();
Dimensiones dimensionesDeZona(const MapaEditor &mapa, Zona zona);
void redimensionarZonaDelMapa(MapaEditor &mapa, Zona zona, Dimensiones nuevas);

#endif // EDITOR_MAPA_EDITOR_H_
