#ifndef EDITOR_DTOS_H_
#define EDITOR_DTOS_H_

#include <vector>

enum class Zona { Granja, Caverna, Pueblo };

enum class Terreno { Pasto, Tierra, Camino, Piso, Pared };

enum class ElementosGranja {
  Cabania,
  Arbol,
  Piedra,
  Cerco,
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
  TipoElemento elemento = 0;
  const char *nombre = 0;
  const char *recurso = 0;
  Recorte recorte = 0;
};

const std::vector<InfoElemento<Terreno>> &terrenosDe(Zona zona);
const std::vector<InfoElemento<ElementosGranja>> &catalogoGranja();
const std::vector<InfoElemento<ElementosCaverna>> &catalogoCaverna();
const std::vector<InfoElemento<ElementosPueblo>> &catalogoPueblo();

#endif // EDITOR_DTOS_H_
