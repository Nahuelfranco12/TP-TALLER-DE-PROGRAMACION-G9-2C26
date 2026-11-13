#ifndef CATALOGO_ELEMENTOS_H_
#define CATALOGO_ELEMENTOS_H_

#include <vector>

#include "elementos_mapa.h"

struct Recorte {
  int x = 0;
  int y = 0;
  int ancho = 0;
  int alto = 0;
};

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

const std::vector<InfoElemento<Terreno>> &terrenosDe(Zona zona);
const std::vector<InfoElemento<ElementosGranja>> &catalogoGranja();
const std::vector<InfoElemento<ElementosCaverna>> &catalogoCaverna();
const std::vector<InfoElemento<ElementosPueblo>> &catalogoPueblo();

#endif // CATALOGO_ELEMENTOS_H_
