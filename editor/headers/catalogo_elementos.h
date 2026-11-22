#ifndef CATALOGO_ELEMENTOS_H_
#define CATALOGO_ELEMENTOS_H_

#include <vector>

#include "elementos_mapa.h"
#include "sprites.h"

template <typename TipoElemento> struct InfoElemento {
  TipoElemento elemento{};
  const char *nombre = nullptr;
  const char *rutaSprite = nullptr;
  Recorte recorte;
};

const InfoElemento<Terreno> *buscarInfoTerreno(Terreno terreno);
const InfoElemento<ElementosGranja> *buscarInfoElemento(ElementosGranja tipo);
const InfoElemento<ElementosCaverna> *buscarInfoElemento(ElementosCaverna tipo);
const InfoElemento<ElementosPueblo> *buscarInfoElemento(ElementosPueblo tipo);

const std::vector<InfoElemento<ElementosGranja>> &
elementosParaColocarEnGranja();
const std::vector<InfoElemento<ElementosCaverna>> &
elementosParaColocarEnCaverna();
const std::vector<InfoElemento<ElementosPueblo>> &
elementosParaColocarEnPueblo();

#endif // CATALOGO_ELEMENTOS_H_
