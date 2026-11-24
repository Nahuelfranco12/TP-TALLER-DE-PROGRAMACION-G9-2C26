#include "ids_mapa.h"

const TablaIds<ElementosGranja> &tablaIds(ElementosGranja) {
  static const TablaIds<ElementosGranja> tabla = {
      {ElementosGranja::Cabania1, ID_CABANIA1},
      {ElementosGranja::Cabania2, ID_CABANIA2},
      {ElementosGranja::Cabania3, ID_CABANIA3},
      {ElementosGranja::Cabania4, ID_CABANIA4},
      {ElementosGranja::Cabania5, ID_CABANIA5},
      {ElementosGranja::SalidaPueblo, ID_SALIDA_PUEBLO},
      {ElementosGranja::Arbol1, ID_ARBOL1},
      {ElementosGranja::Arbol2, ID_ARBOL2},
      {ElementosGranja::Agua, ID_AGUA},
      {ElementosGranja::Piedra, ID_PIEDRA},
      {ElementosGranja::PiedraGrisGrande, ID_PIEDRA_GRIS_GRANDE},
      {ElementosGranja::PiedraGris, ID_PIEDRA_GRIS},
      {ElementosGranja::ArbustoRedondo, ID_ARBUSTO_REDONDO},
      {ElementosGranja::ArbustoGrande, ID_ARBUSTO_GRANDE},
      {ElementosGranja::TroncoCaido, ID_TRONCO_CAIDO},
      {ElementosGranja::Tocon, ID_TOCON},
      {ElementosGranja::BuzonRojo, ID_BUZON_ROJO},
      {ElementosGranja::CartelVacio, ID_CARTEL_VACIO}};
  return tabla;
}

const TablaIds<ElementosCaverna> &tablaIds(ElementosCaverna) {
  static const TablaIds<ElementosCaverna> tabla = {
      {ElementosCaverna::Escalera, ID_ESCALERA},
      {ElementosCaverna::SalidaCaverna, ID_SALIDA_CAVERNA},
      {ElementosCaverna::Barril, ID_BARRIL},
      {ElementosCaverna::Calavera, ID_CALAVERA},
      {ElementosCaverna::Hueso, ID_HUESO},
      {ElementosCaverna::Escombros, ID_ESCOMBROS},
      {ElementosCaverna::Antorcha, ID_ANTORCHA},
      {ElementosCaverna::Candelabro, ID_CANDELABRO},
      {ElementosCaverna::Escudo, ID_ESCUDO},
      {ElementosCaverna::Pozo, ID_POZO}};
  return tabla;
}

const TablaIds<ElementosPueblo> &tablaIds(ElementosPueblo) {
  static const TablaIds<ElementosPueblo> tabla = {
      {ElementosPueblo::NpcMarnie, ID_NPC_MARNIE},
      {ElementosPueblo::NpcClint, ID_NPC_CLINT},
      {ElementosPueblo::NpcPierre, ID_NPC_PIERRE},
      {ElementosPueblo::NpcRobin, ID_NPC_ROBIN},
      {ElementosPueblo::CasaMarnie, ID_CASA_MARNIE},
      {ElementosPueblo::CasaClint, ID_CASA_CLINT},
      {ElementosPueblo::CasaPierre, ID_CASA_PIERRE},
      {ElementosPueblo::CasaRobin, ID_CASA_ROBIN},
      {ElementosPueblo::CentroComunitario, ID_CENTRO_COMUNITARIO},
      {ElementosPueblo::SalidaGranja, ID_SALIDA_GRANJA},
      {ElementosPueblo::EntradaMina, ID_ENTRADA_MINA},
      {ElementosPueblo::FarolNaranja, ID_FAROL_NARANJA},
      {ElementosPueblo::FarolAzul, ID_FAROL_AZUL},
      {ElementosPueblo::BancoMadera, ID_BANCO_MADERA},
      {ElementosPueblo::BuzonGris, ID_BUZON_GRIS},
      {ElementosPueblo::BuzonAzul, ID_BUZON_AZUL}};
  return tabla;
}
