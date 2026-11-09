#ifndef EDITOR_DTOS_H_
#define EDITOR_DTOS_H_

#include <vector>

enum class Zona { Granja, Caverna, Pueblo };

enum class Terreno { Pasto, Tierra, Camino, PisoCaverna, Pared, PisoPueblo };

enum class ElementosGranja {
  Cabania,
  Arbol,
  Piedra,
  CercoFrente,
  CercoCostado,
  EntradaMina,
  SalidaPueblo
};

enum class ElementosCaverna { Escalera, SalidaCaverna };

enum class ElementosPueblo {
  NpcMarnie,
  NpcClint,
  NpcPierre,
  NpcRobin,
  CentroComunitario,
  SalidaGranja
};

struct Recorte {
  int x = 0;
  int y = 0;
  int ancho = 0;
  int alto = 0;
};

template <typename TipoElemento> struct InfoElemento {
  TipoElemento elemento{};
  const char *nombre = nullptr;
  const char *recurso = nullptr;
  Recorte recorte;
};

const InfoElemento<Terreno> *infoTerreno(Terreno terreno);
const std::vector<InfoElemento<Terreno>> &terrenosDe(Zona zona);
const std::vector<InfoElemento<ElementosGranja>> &catalogoGranja();
const std::vector<InfoElemento<ElementosCaverna>> &catalogoCaverna();
const std::vector<InfoElemento<ElementosPueblo>> &catalogoPueblo();
const InfoElemento<ElementosGranja> *infoDe(ElementosGranja tipo);
const InfoElemento<ElementosCaverna> *infoDe(ElementosCaverna tipo);
const InfoElemento<ElementosPueblo> *infoDe(ElementosPueblo tipo);

#endif // EDITOR_DTOS_H_
