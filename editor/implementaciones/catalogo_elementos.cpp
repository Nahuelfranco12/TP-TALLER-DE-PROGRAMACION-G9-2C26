#include "catalogo_elementos.h"

#include <initializer_list>
#include <vector>

#include "constantes_mapa.h"
#include "constantes_qt.h"

namespace {
const std::vector<InfoElemento<Terreno>> &terrenosDisponiblesEnZona(Zona zona) {
  static const std::vector<InfoElemento<Terreno>> granja = {
      {Terreno::Pasto, TEXTO_PASTO, RUTA_SUELO, RECORTE_PASTO}};
  static const std::vector<InfoElemento<Terreno>> caverna = {
      {Terreno::PisoCaverna, TEXTO_PISO, RUTA_CAVERNA, RECORTE_PISO_CAVERNA},
      {Terreno::Pared, TEXTO_PARED, RUTA_CAVERNA, RECORTE_PARED_CAVERNA}};
  static const std::vector<InfoElemento<Terreno>> pueblo = {
      {Terreno::PisoPueblo, TEXTO_PISO_PUEBLO, RUTA_PISO_PIEDRA,
       RECORTE_PISO_PUEBLO}};
  switch (zona) {
  case Zona::Granja:
    return granja;
  case Zona::Caverna:
    return caverna;
  case Zona::Pueblo:
    return pueblo;
  }
  return granja;
}

template <typename T>
const InfoElemento<T> *
buscarInfoEnCatalogo(const std::vector<InfoElemento<T>> &catalogo, T tipo) {
  for (const InfoElemento<T> &info : catalogo)
    if (info.elemento == tipo)
      return &info;
  return nullptr;
}
} // namespace

const std::vector<InfoElemento<ElementosGranja>> &
elementosParaColocarEnGranja() {
  static const std::vector<InfoElemento<ElementosGranja>> catalogo = {
      {ElementosGranja::Cabania1, TEXTO_CABANIA1, RUTA_CABANIAS,
       RECORTE_CABANIA1},
      {ElementosGranja::Cabania2, TEXTO_CABANIA2, RUTA_CABANIAS,
       RECORTE_CABANIA2},
      {ElementosGranja::Cabania3, TEXTO_CABANIA3, RUTA_CABANIAS,
       RECORTE_CABANIA3},
      {ElementosGranja::Cabania4, TEXTO_CABANIA4, RUTA_CABANIAS,
       RECORTE_CABANIA4},
      {ElementosGranja::Cabania5, TEXTO_CABANIA5, RUTA_CABANIAS,
       RECORTE_CABANIA5},
      {ElementosGranja::SalidaPueblo, TEXTO_SALIDA_PUEBLO, RUTA_OBJETOS,
       RECORTE_SALIDA_PUEBLO},
      {ElementosGranja::Arbol1, TEXTO_ARBOL1, RUTA_ARBOL1, {}},
      {ElementosGranja::Arbol2, TEXTO_ARBOL2, RUTA_ARBOL2, {}},
      {ElementosGranja::Agua, TEXTO_AGUA, RUTA_NATURALEZA, RECORTE_AGUA},
      {ElementosGranja::Piedra, TEXTO_PIEDRA, RUTA_PIEDRAS, RECORTE_PIEDRA},
      {ElementosGranja::PiedraGrisGrande, TEXTO_PIEDRA_GRIS_GRANDE,
       RUTA_NATURALEZA, RECORTE_PIEDRA_GRIS_GRANDE},
      {ElementosGranja::PiedraGris, TEXTO_PIEDRA_GRIS, RUTA_NATURALEZA,
       RECORTE_PIEDRA_GRIS},
      {ElementosGranja::ArbustoRedondo, TEXTO_ARBUSTO_REDONDO, RUTA_NATURALEZA,
       RECORTE_ARBUSTO_REDONDO},
      {ElementosGranja::ArbustoGrande, TEXTO_ARBUSTO_GRANDE, RUTA_NATURALEZA,
       RECORTE_ARBUSTO_GRANDE},
      {ElementosGranja::TroncoCaido, TEXTO_TRONCO_CAIDO, RUTA_NATURALEZA,
       RECORTE_TRONCO_CAIDO},
      {ElementosGranja::Tocon, TEXTO_TRONCO_CORTADO, RUTA_NATURALEZA,
       RECORTE_TOCON},
      {ElementosGranja::BuzonRojo, TEXTO_BUZON_ROJO, RUTA_OBJETOS,
       RECORTE_BUZON_ROJO},
      {ElementosGranja::CartelVacio, TEXTO_CARTEL_VACIO, RUTA_OBJETOS,
       RECORTE_CARTEL_VACIO}};
  return catalogo;
}

const std::vector<InfoElemento<ElementosCaverna>> &
elementosParaColocarEnCaverna() {
  static const std::vector<InfoElemento<ElementosCaverna>> catalogo = {
      {ElementosCaverna::Escalera, TEXTO_ESCALERA, RUTA_CAVERNA,
       RECORTE_ESCALERA},
      {ElementosCaverna::SalidaCaverna, TEXTO_SALIDA_CAVERNA, RUTA_CAVERNA,
       RECORTE_PUERTA_CAVERNA},
      {ElementosCaverna::Barril, TEXTO_BARRIL, RUTA_CAVERNA, RECORTE_BARRIL},
      {ElementosCaverna::Calavera, TEXTO_CALAVERA, RUTA_CAVERNA,
       RECORTE_CALAVERA},
      {ElementosCaverna::Hueso, TEXTO_HUESO, RUTA_CAVERNA, RECORTE_HUESO},
      {ElementosCaverna::Escombros, TEXTO_ESCOMBROS, RUTA_CAVERNA,
       RECORTE_ESCOMBROS},
      {ElementosCaverna::Antorcha, TEXTO_ANTORCHA, RUTA_CAVERNA,
       RECORTE_ANTORCHA},
      {ElementosCaverna::Candelabro, TEXTO_CANDELABRO, RUTA_CAVERNA,
       RECORTE_CANDELABRO},
      {ElementosCaverna::Escudo, TEXTO_ESCUDO, RUTA_CAVERNA, RECORTE_ESCUDO},
      {ElementosCaverna::Pozo, TEXTO_POZO, RUTA_POZO, RECORTE_POZO}};
  return catalogo;
}

const std::vector<InfoElemento<ElementosPueblo>> &
elementosParaColocarEnPueblo() {
  static const std::vector<InfoElemento<ElementosPueblo>> catalogo = {
      {ElementosPueblo::CasaMarnie, TEXTO_CASA_MARNIE, RUTA_CASA_NPC,
       RECORTE_CASA_MARNIE},
      {ElementosPueblo::NpcMarnie, TEXTO_MARNIE, RUTA_MARNIE,
       RECORTE_MARNIE_ROBIN},
      {ElementosPueblo::CasaClint, TEXTO_CASA_CLINT, RUTA_CASA_NPC,
       RECORTE_CASA_CLINT},
      {ElementosPueblo::NpcClint, TEXTO_CLINT, RUTA_CLINT,
       RECORTE_PIERRE_CLINT},
      {ElementosPueblo::CasaPierre, TEXTO_CASA_PIERRE, RUTA_CASA_NPC,
       RECORTE_CASA_PIERRE},
      {ElementosPueblo::NpcPierre, TEXTO_PIERRE, RUTA_PIERRE,
       RECORTE_PIERRE_CLINT},
      {ElementosPueblo::CasaRobin, TEXTO_CASA_ROBIN, RUTA_CASA_NPC,
       RECORTE_CASA_ROBIN},
      {ElementosPueblo::NpcRobin, TEXTO_ROBIN, RUTA_ROBIN,
       RECORTE_MARNIE_ROBIN},
      {ElementosPueblo::CentroComunitario, TEXTO_CENTRO_COMUNITARIO,
       RUTA_CENTRO_COMUNITARIO, RECORTE_CENTRO_COMUNITARIO},
      {ElementosPueblo::EntradaMina, TEXTO_ENTRADA_MINA, RUTA_CAVERNA,
       RECORTE_ENTRADA_MINA},
      {ElementosPueblo::SalidaGranja, TEXTO_SALIDA_GRANJA, RUTA_OBJETOS,
       RECORTE_SALIDA_PUEBLO},
      {ElementosPueblo::FarolNaranja, TEXTO_FAROL_NARANJA, RUTA_OBJETOS,
       RECORTE_FAROL_NARANJA},
      {ElementosPueblo::FarolAzul, TEXTO_FAROL_AZUL, RUTA_OBJETOS,
       RECORTE_FAROL_AZUL},
      {ElementosPueblo::BancoMadera, TEXTO_BANCO_MADERA, RUTA_OBJETOS,
       RECORTE_BANCO_MADERA},
      {ElementosPueblo::BuzonGris, TEXTO_BUZON_GRIS, RUTA_OBJETOS,
       RECORTE_BUZON_GRIS},
      {ElementosPueblo::BuzonAzul, TEXTO_BUZON_AZUL, RUTA_OBJETOS,
       RECORTE_BUZON_AZUL}};
  return catalogo;
}

const InfoElemento<Terreno> *buscarInfoTerreno(Terreno terreno) {
  for (Zona zona : {Zona::Granja, Zona::Caverna, Zona::Pueblo}) {
    const InfoElemento<Terreno> *info =
        buscarInfoEnCatalogo(terrenosDisponiblesEnZona(zona), terreno);
    if (info != nullptr)
      return info;
  }
  return nullptr;
}

const InfoElemento<ElementosGranja> *buscarInfoElemento(ElementosGranja tipo) {
  return buscarInfoEnCatalogo(elementosParaColocarEnGranja(), tipo);
}

const InfoElemento<ElementosCaverna> *
buscarInfoElemento(ElementosCaverna tipo) {
  return buscarInfoEnCatalogo(elementosParaColocarEnCaverna(), tipo);
}

const InfoElemento<ElementosPueblo> *buscarInfoElemento(ElementosPueblo tipo) {
  return buscarInfoEnCatalogo(elementosParaColocarEnPueblo(), tipo);
}
