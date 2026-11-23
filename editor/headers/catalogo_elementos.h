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

const InfoElemento<Terreno> *infoTerreno(Terreno terreno);
const InfoElemento<ElementosGranja> *infoDe(ElementosGranja tipo);
const InfoElemento<ElementosCaverna> *infoDe(ElementosCaverna tipo);
const InfoElemento<ElementosPueblo> *infoDe(ElementosPueblo tipo);

const std::vector<InfoElemento<ElementosGranja>> &catalogoGranja();
const std::vector<InfoElemento<ElementosCaverna>> &catalogoCaverna();
const std::vector<InfoElemento<ElementosPueblo>> &catalogoPueblo();

#endif // CATALOGO_ELEMENTOS_H_
