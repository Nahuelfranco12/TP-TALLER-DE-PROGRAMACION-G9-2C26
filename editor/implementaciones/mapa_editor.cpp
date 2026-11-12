#include "mapa_editor.h"
#include "constantes.h"
#include "editor_dtos.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

MapaEditor crearMapaPredeterminado() {
  MapaZona<ElementosCaverna> nivelBase(Dimensiones{}, Terreno::PisoCaverna);
  pintarBorde(nivelBase, Terreno::Pared);
  std::vector<MapaZona<ElementosCaverna>> niveles(CANTIDAD_NIVELES_CAVERNA,
                                                  nivelBase);
  return MapaEditor{
      "", MapaZona<ElementosGranja>(Dimensiones{}, Terreno::Pasto),
      std::move(niveles),
      MapaZona<ElementosPueblo>(Dimensiones{}, Terreno::PisoPueblo)};
}

CeldasOcupadasPorObjeto OcupadaPor(ElementosGranja tipo) {
  switch (tipo) {
  case ElementosGranja::Cabania1:
  case ElementosGranja::Cabania2:
  case ElementosGranja::Cabania3:
  case ElementosGranja::Cabania4:
  case ElementosGranja::Cabania5:
  case ElementosGranja::Cabania6:
    return {TAMANIO_OCUPADO_CABANIA_ANCHO, TAMANIO_OCUPADO_CABANIA_ALTO};
  case ElementosGranja::Arbol1:
  case ElementosGranja::Arbol2:
    // case ElementosGranja::Arbol3:
    // case ElementosGranja::Arbol4:
    // case ElementosGranja::Arbol5:
    return {TAMANIO_OCUPADO_ASSET_NORMAL, TAMANIO_OCUPADO_ARBOL_ALTO};
  case ElementosGranja::Agua:
    return {TAMANIO_OCUPADO_AGUA_ANCHO, TAMANIO_OCUPADO_AGUA_ALTO};
  default:
    return {TAMANIO_OCUPADO_ASSET_NORMAL, TAMANIO_OCUPADO_ASSET_NORMAL};
  }
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
  case ElementosPueblo::CasaChica:
    return {TAMANIO_OCUPADO_CASA_CHICA_ANCHO, TAMANIO_OCUPADO_CASA_CHICA_ALTO};
  case ElementosPueblo::CasaMediana:
    return {TAMANIO_OCUPADO_CASA_MEDIANA_ANCHO,
            TAMANIO_OCUPADO_CASA_MEDIANA_ALTO};
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

bool esUnico(ElementosGranja tipo) {
  switch (tipo) {
  case ElementosGranja::Cabania1:
  case ElementosGranja::Cabania2:
  case ElementosGranja::Cabania3:
  case ElementosGranja::Cabania4:
  case ElementosGranja::Cabania5:
  case ElementosGranja::Cabania6:
  // case ElementosGranja::EntradaMina:
  case ElementosGranja::SalidaPueblo:
    return true;
  default:
    return false;
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
