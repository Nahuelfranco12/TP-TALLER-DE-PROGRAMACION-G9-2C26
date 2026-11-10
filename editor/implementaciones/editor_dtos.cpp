#include "editor_dtos.h"

#include <vector>

#include "constantes.h"

const std::vector<InfoElemento<Terreno>> &terrenosDe(Zona zona) {
  static const std::vector<InfoElemento<Terreno>> granja = {
      {Terreno::Pasto, TEXTO_PASTO, RUTA_SUELO, RECORTE_PASTO}};
  static const std::vector<InfoElemento<Terreno>> caverna = {
      {Terreno::PisoCaverna, TEXTO_PISO, RUTA_CAVERNA, RECORTE_PISO_CAVERNA}};
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

const std::vector<InfoElemento<ElementosGranja>> &catalogoGranja() {
  static const std::vector<InfoElemento<ElementosGranja>> catalogo = {
      {ElementosGranja::Cabania, TEXTO_CABANIA, RUTA_CASA, RECORTE_CABANIA},
      {ElementosGranja::Arbol1, TEXTO_ARBOL, RUTA_ARBOL1, {}},
      {ElementosGranja::Arbol2, TEXTO_ARBOL, RUTA_ARBOL2, {}},
      {ElementosGranja::Piedra, TEXTO_PIEDRA, RUTA_PIEDRAS, RECORTE_PIEDRA},
      //{ElementosGranja::CercoFrente, TEXTO_CERCO, RUTA_CERCO_FRENTE, RECORTE_CERCO_FRENTE},
      //{ElementosGranja::CercoCostado, TEXTO_CERCO, RUTA_CERCO_COSTADO,RECORTE_CERCO_COSTADO},
      //{ElementosGranja::EntradaMina, TEXTO_ENTRADA_MINA,
      // RUTA_CAVERNA,RECORTE_ENTRADA_MINA},
      {ElementosGranja::SalidaPueblo, TEXTO_SALIDA_PUEBLO, RUTA_OBJETOS,
       RECORTE_SALIDA_PUEBLO}};
  return catalogo;
}

const std::vector<InfoElemento<ElementosCaverna>> &catalogoCaverna() {
  static const std::vector<InfoElemento<ElementosCaverna>> catalogo = {
      {ElementosCaverna::Escalera, TEXTO_ESCALERA, RUTA_CAVERNA,
       RECORTE_ESCALERA},
      {ElementosCaverna::SalidaCaverna, TEXTO_SALIDA_CAVERNA, SIN_ASSET, {}}};
  return catalogo;
}

const std::vector<InfoElemento<ElementosPueblo>> &catalogoPueblo() {
  static const std::vector<InfoElemento<ElementosPueblo>> catalogo = {
      {ElementosPueblo::NpcMarnie, TEXTO_MARNIE, RUTA_MARNIE,
       RECORTE_MERNIE_ROBIN},
      {ElementosPueblo::NpcClint, TEXTO_CLINT, RUTA_CLINT, RECORTE_PC},
      {ElementosPueblo::NpcPierre, TEXTO_PIERRE, RUTA_PIERRE, RECORTE_PC},
      {ElementosPueblo::NpcRobin, TEXTO_ROBIN, RUTA_ROBIN,
       RECORTE_MERNIE_ROBIN},
      {ElementosPueblo::CentroComunitario, TEXTO_CENTRO_COMUNITARIO,
       RUTA_CENTRO_COMUNITARIO, RECORTE_CENTRO_COMUNITARIO}
      //{ElementosPueblo::SalidaGranja, TEXTO_SALIDA_GRANJA, SIN_ASSET, {}
  };
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
