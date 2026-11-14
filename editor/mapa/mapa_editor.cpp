#include "mapa_editor.h"
#include "constantes_mapa.h"

#include <utility>
#include <vector>

Terreno pisoBaseDe(Zona zona) {
  switch (zona) {
  case Zona::Granja:
    return Terreno::Pasto;
  case Zona::Caverna:
    return Terreno::PisoCaverna;
  case Zona::Pueblo:
    return Terreno::PisoPueblo;
  }
  return Terreno::Pasto;
}

MapaZona<ElementosCaverna> crearNivelCaverna(Dimensiones dimensiones) {
  MapaZona<ElementosCaverna> nivel(dimensiones, pisoBaseDe(Zona::Caverna));
  pintarBorde(nivel, Terreno::Pared);
  return nivel;
}

MapaEditor crearMapaPredeterminado() {
  std::vector<MapaZona<ElementosCaverna>> niveles(
      CANTIDAD_NIVELES_CAVERNA, crearNivelCaverna(Dimensiones{}));
  return MapaEditor{
      "", MapaZona<ElementosGranja>(Dimensiones{}, pisoBaseDe(Zona::Granja)),
      std::move(niveles),
      MapaZona<ElementosPueblo>(Dimensiones{}, pisoBaseDe(Zona::Pueblo))};
}

Dimensiones dimensionesDe(const MapaEditor &mapa, Zona zona) {
  switch (zona) {
  case Zona::Granja:
    return mapa.granja.tamanio();
  case Zona::Caverna:
    return mapa.nivelesCaverna.front().tamanio();
  case Zona::Pueblo:
    return mapa.pueblo.tamanio();
  }
  return Dimensiones{};
}

void redimensionar(MapaEditor &mapa, Zona zona, Dimensiones nuevas) {
  if (!dimensionesValidas(nuevas))
    throw std::invalid_argument(ERROR_DIMENSIONES_FUERA_DE_RANGO);
  switch (zona) {
  case Zona::Granja:
    mapa.granja.redimensionar(nuevas);
    break;
  case Zona::Caverna:
    for (auto &nivel : mapa.nivelesCaverna) {
      pintarBorde(nivel, pisoBaseDe(Zona::Caverna));
      nivel.redimensionar(nuevas);
      pintarBorde(nivel, Terreno::Pared);
    }
    break;
  case Zona::Pueblo:
    mapa.pueblo.redimensionar(nuevas);
    break;
  }
}

bool esCabania(ElementosGranja tipo) {
  switch (tipo) {
  case ElementosGranja::Cabania1:
  case ElementosGranja::Cabania2:
  case ElementosGranja::Cabania3:
  case ElementosGranja::Cabania4:
  case ElementosGranja::Cabania5:
    return true;
  default:
    return false;
  }
}

CeldasOcupadasPorObjeto OcupadaPor(ElementosGranja tipo) {
  if (esCabania(tipo))
    return {TAMANIO_OCUPADO_CABANIA_ANCHO, TAMANIO_OCUPADO_CABANIA_ALTO};
  switch (tipo) {
  case ElementosGranja::Arbol1:
  case ElementosGranja::Arbol2:
    return {TAMANIO_OCUPADO_ASSET_NORMAL, TAMANIO_OCUPADO_ARBOL_ALTO};
  case ElementosGranja::Agua:
    return {TAMANIO_OCUPADO_AGUA_ANCHO, TAMANIO_OCUPADO_AGUA_ALTO};
  default:
    return {TAMANIO_OCUPADO_ASSET_NORMAL, TAMANIO_OCUPADO_ASSET_NORMAL};
  }
}

bool esUnico(ElementosGranja tipo) {
  return esCabania(tipo) || tipo == ElementosGranja::SalidaPueblo;
}

CeldasOcupadasPorObjeto OcupadaPor(ElementosCaverna tipo) {
  if (tipo == ElementosCaverna::SalidaCaverna)
    return {TAMANIO_OCUPADO_PUERTA_CAVERNA_ANCHO, TAMANIO_OCUPADO_ASSET_NORMAL};
  return {TAMANIO_OCUPADO_ASSET_NORMAL, TAMANIO_OCUPADO_ASSET_NORMAL};
}

CeldasOcupadasPorObjeto OcupadaPor(ElementosPueblo tipo) {
  switch (tipo) {
  case ElementosPueblo::CentroComunitario:
    return {TAMANIO_OCUPADO_CENTROCOM_ANCHO, TAMANIO_OCUPADO_CENTROCOM_ALTO};
  case ElementosPueblo::FarolNaranja:
  case ElementosPueblo::FarolAzul:
    return {TAMANIO_OCUPADO_ASSET_NORMAL, TAMANIO_OCUPADO_FAROL_ALTO};
  case ElementosPueblo::BancoMadera:
    return {TAMANIO_OCUPADO_BANCO_ANCHO, TAMANIO_OCUPADO_ASSET_NORMAL};
  case ElementosPueblo::CasaRobin:
  case ElementosPueblo::CasaPierre:
  case ElementosPueblo::CasaMarnie:
  case ElementosPueblo::CasaClint:
    return {TAMANIO_ANCHO_CASA_NPC, TAMANIO_ALTO_CASA_NPC};
  case ElementosPueblo::NpcPierre:
  case ElementosPueblo::NpcMarnie:
  case ElementosPueblo::NpcRobin:
  case ElementosPueblo::NpcClint:
    return {TAMANIO_ALTO_ANCHO_NPC, TAMANIO_ALTO_ANCHO_NPC};
  default:
    return {TAMANIO_OCUPADO_ASSET_NORMAL, TAMANIO_OCUPADO_ASSET_NORMAL};
  }
}

bool esUnico(ElementosCaverna tipo) {
  return tipo == ElementosCaverna::Escalera ||
         tipo == ElementosCaverna::SalidaCaverna;
}

bool esUnico(ElementosPueblo tipo) {
  switch (tipo) {
  case ElementosPueblo::NpcMarnie:
  case ElementosPueblo::NpcClint:
  case ElementosPueblo::NpcPierre:
  case ElementosPueblo::NpcRobin:
  case ElementosPueblo::CasaMarnie:
  case ElementosPueblo::CasaClint:
  case ElementosPueblo::CasaPierre:
  case ElementosPueblo::CasaRobin:
  case ElementosPueblo::CentroComunitario:
  case ElementosPueblo::SalidaGranja:
  case ElementosPueblo::EntradaMina:
    return true;
  default:
    return false;
  }
}
