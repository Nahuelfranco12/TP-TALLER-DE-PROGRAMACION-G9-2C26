#include "editor_dtos.h"

#include <vector>

#include "constantes.h"

const std::vector<InfoElemento<Terreno>> &terrenosDe(Zona zona) {
  static const std::vector<InfoElemento<Terreno>> granja = {
      {Terreno::Pasto, TEXTO_PASTO, SUELO, RECORTE_PASTO},
      {Terreno::Tierra, TEXTO_TIERRA, SUELO, RECORTE_TIERRA}};
  static const std::vector<InfoElemento<Terreno>> caverna = {
      {Terreno::PisoCaverna, TEXTO_PISO, DUNGEON, RECORTE_PISO_CAVERNA},
      {Terreno::Pared, TEXTO_PARED, DUNGEON, RECORTE_PARED_CAVERNA}};
  static const std::vector<InfoElemento<Terreno>> pueblo = {
      {Terreno::PisoPueblo, TEXTO_PISO_PUEBLO, PISO_PIEDRA,
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

const std::vector<InfoElemento<ElementosGranja>> &catalogoGranja() {
  static const std::vector<InfoElemento<ElementosGranja>> catalogo = {
      {ElementosGranja::Cabania, TEXTO_CABANIA, CASA, RECORTE_CABANIA},
      {ElementosGranja::Arbol, TEXTO_ARBOL, ARBOL, {}},
      {ElementosGranja::Piedra, TEXTO_PIEDRA, PIEDRAS, RECORTE_PIEDRA},
      {ElementosGranja::CercoFrente, TEXTO_CERCO, CERCO_FRENTE,
       RECORTE_CERCO_FRENTE},
      {ElementosGranja::CercoCostado, TEXTO_CERCO, CERCO_COSTADO,
       RECORTE_CERCO_COSTADO},
      {ElementosGranja::EntradaMina, TEXTO_ENTRADA_MINA, DUNGEON,
       RECORTE_ENTRADA_MINA},
      {ElementosGranja::SalidaPueblo, TEXTO_SALIDA_PUEBLO, OBJETOS,
       RECORTE_SALIDA_PUEBLO}};
  return catalogo;
}

const std::vector<InfoElemento<ElementosCaverna>> &catalogoCaverna() {
  static const std::vector<InfoElemento<ElementosCaverna>> catalogo = {
      {ElementosCaverna::Escalera, TEXTO_ESCALERA, DUNGEON, RECORTE_ESCALERA},
      {ElementosCaverna::SalidaCaverna, TEXTO_SALIDA_CAVERNA, SIN_ASSET, {}}};
  return catalogo;
}

const std::vector<InfoElemento<ElementosPueblo>> &catalogoPueblo() {
  static const std::vector<InfoElemento<ElementosPueblo>> catalogo = {
      {ElementosPueblo::NpcMarnie, TEXTO_MARNIE, RUTA_MARNIE, RECORTE_MR},
      {ElementosPueblo::NpcClint, TEXTO_CLINT, RUTA_CLINT, RECORTE_PC},
      {ElementosPueblo::NpcPierre, TEXTO_PIERRE, RUTA_PIERRE, RECORTE_PC},
      {ElementosPueblo::NpcRobin, TEXTO_ROBIN, RUTA_ROBIN, RECORTE_MR},
      {ElementosPueblo::CentroComunitario, TEXTO_CENTRO_COMUNITARIO,
       RUTA_CENTRO_COMUNITARIO, RECORTE_CENTRO_COMUNITARIO},
      {ElementosPueblo::SalidaGranja, TEXTO_SALIDA_GRANJA, SIN_ASSET, {}}};
  return catalogo;
}

const InfoElemento<Terreno> *infoTerreno(Terreno terreno) {
  for (Zona zona : {Zona::Granja, Zona::Caverna, Zona::Pueblo})
    for (const auto &info : terrenosDe(zona))
      if (info.elemento == terreno)
        return &info;
  return nullptr;
}

namespace {
template <typename T>
const InfoElemento<T> *buscar(const std::vector<InfoElemento<T>> &catalogo,
                              T tipo) {
  for (const auto &info : catalogo)
    if (info.elemento == tipo)
      return &info;
  return nullptr;
}
} // namespace

const InfoElemento<ElementosGranja> *infoDe(ElementosGranja tipo) {
  return buscar(catalogoGranja(), tipo);
}

const InfoElemento<ElementosCaverna> *infoDe(ElementosCaverna tipo) {
  return buscar(catalogoCaverna(), tipo);
}

const InfoElemento<ElementosPueblo> *infoDe(ElementosPueblo tipo) {
  return buscar(catalogoPueblo(), tipo);
}
