#ifndef EDITOR_DTOS_H_
#define EDITOR_DTOS_H_

#include <vector>

enum class Zona { Granja, Caverna, Pueblo };

enum class Terreno { Pasto, Tierra, Camino, PisoCaverna, Pared, PisoPueblo };

enum class ElementosGranja {
  Cabania1,
  Cabania2,
  Cabania3,
  Cabania4,
  Cabania5,
  Cabania6,
  Arbol1,
  Arbol2,
  // Arbol3,
  // Arbol4,
  // Arbol5,
  Piedra,
  Agua,
  ArbustoRedondo,
  ArbustoGrande,
  PiedraGrisGrande,
  PiedraGris,
  TroncoTirado,
  Tocon,
  BuzonRojo,
  CartelVacio,
  //EntradaMina,
  SalidaPueblo
};

enum class ElementosCaverna { Escalera, SalidaCaverna,
Barril,Calavera,Hueso,Escombros,Antorchas,Candelabro,Escudo};

enum class ElementosPueblo {
  NpcMarnie,
  NpcClint,
  NpcPierre,
  NpcRobin,
  CentroComunitario,
  SalidaGranja,
  EntradaMina,
  FarolNaranja,
  FarolAzul,
  BancoMadera,
  BuzonGris,
  BuzonAzul,
  CasaChica,
  CasaMediana,
  CasaMarnie,
  CasaClint,
  CasaPierre,
  CasaRobin
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

#endif // EDITOR_DTOS_H_
