#ifndef EDITOR_DTOS_H_
#define EDITOR_DTOS_H_

#include <vector>

enum class Zona { Granja, Caverna, Pueblo };

enum class Terreno { Pasto, Tierra, Camino, Agua, Piso, Pared };

enum class ElementosGranja {
  Cabania,
  Arbol,
  Piedra,
  Arbusto,
  Cerco,
  EntradaMina,
  SalidaPueblo
};

enum class ElementosCaverna { Escalera, salidaCaverna };

enum class ElementosPueblo {
  npcMarnie,
  npcCLint,
  npcPierre,
  npcRobin,
  centroComunitario,
  SalidaGranja
};

template <typename tipoElemento> struct InfoElemento {
  tipoElemento elemento;
  const char *nombre;
  const char *recurso;
};

const std::vector<InfoElemento<Terreno>> &terrenosDe(Zona zona);
const std::vector<InfoElemento<ElementosGranja>> &catalogoGranja();
const std::vector<InfoElemento<ElementosCaverna>> &catalogoCaverna();
const std::vector<InfoElemento<ElementosPueblo>> &catalogoPueblo();

#endif // EDITOR_DTOS_H_
