#include "editor_dtos.h"

#include "constantes.h"

const std::vector<InfoElemento<Terreno>> &terrenosDe(Zona zona) {
  static const std::vector<InfoElemento<Terreno>> exterior = {
      {Terreno::Pasto, TEXTO_PASTO, SUELO, RECORTE_PASTO},
      {Terreno::Tierra, TEXTO_TIERRA, SUELO, RECORTE_TIERRA},
      {Terreno::Camino, TEXTO_CAMINO, SIN_ASSET, {}}};
  static const std::vector<InfoElemento<Terreno>> caverna = {
      {Terreno::Piso, TEXTO_PISO, DUNGEON, RECORTE_PISO_CAVERNA},
      {Terreno::Pared, TEXTO_PARED, DUNGEON, RECORTE_PARED_CAVERNA}};
  if (zona == Zona::Caverna)
    return caverna;
  return exterior;
}

const std::vector<InfoElemento<ElementosGranja>> &catalogoGranja() {
  static const std::vector<InfoElemento<ElementosGranja>> catalogo = {
      {ElementosGranja::Cabania, TEXTO_CABANIA, CASA, RECORTE_CABANIA},
      {ElementosGranja::Arbol, TEXTO_ARBOL, ARBOL, {}},
      {ElementosGranja::Piedra, TEXTO_PIEDRA, PIEDRAS, RECORTE_PIEDRA},
      {ElementosGranja::Cerco, TEXTO_CERCO, CERCO, RECORTE_CERCO},
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
