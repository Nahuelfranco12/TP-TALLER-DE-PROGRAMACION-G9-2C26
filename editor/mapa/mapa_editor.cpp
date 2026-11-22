#include "mapa_editor.h"
#include "constantes_mapa.h"
#include "elementos_mapa.h"

#include <utility>
#include <vector>

Terreno terrenoBaseDeZona(Zona zona) {
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

MapaZona<ElementosCaverna> crearNivelCavernaConParedes(Dimensiones dimensiones) {
  MapaZona<ElementosCaverna> nivel(dimensiones, terrenoBaseDeZona(Zona::Caverna));
  pintarBordeDeZona(nivel, Terreno::Pared);
  return nivel;
}

MapaEditor crearMapaVacio() {
  std::vector<MapaZona<ElementosCaverna>> niveles(
      CANTIDAD_NIVELES_CAVERNA, crearNivelCavernaConParedes(Dimensiones{}));
  return MapaEditor{
      "", MapaZona<ElementosGranja>(Dimensiones{}, terrenoBaseDeZona(Zona::Granja)),
      std::move(niveles),
      MapaZona<ElementosPueblo>(Dimensiones{}, terrenoBaseDeZona(Zona::Pueblo))};
}

Dimensiones dimensionesDeZona(const MapaEditor &mapa, Zona zona) {
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

void redimensionarZonaDelMapa(MapaEditor &mapa, Zona zona, Dimensiones nuevas) {
  if (!sonDimensionesValidas(nuevas))
    throw std::invalid_argument(TEXTO_ERROR_DIMENSIONES_ZONA);
  switch (zona) {
  case Zona::Granja:
    mapa.granja.redimensionarZona(nuevas);
    break;
  case Zona::Caverna:
    for (auto &nivel : mapa.nivelesCaverna) {
      pintarBordeDeZona(nivel, terrenoBaseDeZona(Zona::Caverna));
      nivel.redimensionarZona(nuevas);
      pintarBordeDeZona(nivel, Terreno::Pared);
    }
    break;
  case Zona::Pueblo:
    mapa.pueblo.redimensionarZona(nuevas);
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

TamanioEnCeldas tamanioEnCeldasDe(ElementosGranja tipo) {
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

bool esUnicoEnZona(ElementosGranja tipo) {
  return esCabania(tipo) || tipo == ElementosGranja::SalidaPueblo;
}

TamanioEnCeldas tamanioEnCeldasDe(ElementosCaverna tipo) {
  switch (tipo) {
  case ElementosCaverna::Pozo:
    return {TAMANIO_OCUPADO_POZO_ANCHO_ALTO, TAMANIO_OCUPADO_POZO_ANCHO_ALTO};
  case ElementosCaverna::SalidaCaverna:
    return {TAMANIO_OCUPADO_PUERTA_CAVERNA_ANCHO, TAMANIO_OCUPADO_ASSET_NORMAL};
  default:
    return {TAMANIO_OCUPADO_ASSET_NORMAL, TAMANIO_OCUPADO_ASSET_NORMAL};
  }
}

TamanioEnCeldas tamanioEnCeldasDe(ElementosPueblo tipo) {
  switch (tipo) {
  case ElementosPueblo::CentroComunitario:
    return {TAMANIO_OCUPADO_CENTRO_COMUNITARIO_ANCHO, TAMANIO_OCUPADO_CENTRO_COMUNITARIO_ALTO};
  case ElementosPueblo::FarolNaranja:
  case ElementosPueblo::FarolAzul:
    return {TAMANIO_OCUPADO_ASSET_NORMAL, TAMANIO_OCUPADO_FAROL_ALTO};
  case ElementosPueblo::BancoMadera:
    return {TAMANIO_OCUPADO_BANCO_ANCHO, TAMANIO_OCUPADO_ASSET_NORMAL};
  case ElementosPueblo::CasaRobin:
  case ElementosPueblo::CasaPierre:
  case ElementosPueblo::CasaMarnie:
  case ElementosPueblo::CasaClint:
    return {TAMANIO_OCUPADO_CASA_NPC_ANCHO, TAMANIO_OCUPADO_CASA_NPC_ALTO};
  case ElementosPueblo::NpcPierre:
  case ElementosPueblo::NpcMarnie:
  case ElementosPueblo::NpcRobin:
  case ElementosPueblo::NpcClint:
    return {TAMANIO_OCUPADO_NPC_ANCHO_ALTO, TAMANIO_OCUPADO_NPC_ANCHO_ALTO};
  default:
    return {TAMANIO_OCUPADO_ASSET_NORMAL, TAMANIO_OCUPADO_ASSET_NORMAL};
  }
}

bool esUnicoEnZona(ElementosCaverna tipo) {
  return tipo == ElementosCaverna::Escalera ||
         tipo == ElementosCaverna::SalidaCaverna ||
         tipo == ElementosCaverna::Pozo;
}

bool esUnicoEnZona(ElementosPueblo tipo) {
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
