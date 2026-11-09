#include "mapa_editor.h"

#include <utility>
#include <vector>

MapaEditor crearMapaPredeterminado() {
  std::vector<MapaZona<ElementosCaverna>> niveles(
      CANTIDAD_NIVELES_CAVERNA,
      MapaZona<ElementosCaverna>(Dimensiones{}, Terreno::PisoCaverna));
  return MapaEditor{
      "", MapaZona<ElementosGranja>(Dimensiones{}, Terreno::Pasto),
      std::move(niveles),
      MapaZona<ElementosPueblo>(Dimensiones{}, Terreno::PisoPueblo)};
}

Huella huellaDe(ElementosGranja tipo) {
  if (tipo == ElementosGranja::Cabania)
    return Huella{HUELLA_CABANIA_ANCHO, HUELLA_CABANIA_ALTO};
  return Huella{HUELLA_SIMPLE, HUELLA_SIMPLE};
}

Huella huellaDe(ElementosCaverna) {
  return Huella{HUELLA_SIMPLE, HUELLA_SIMPLE};
}

Huella huellaDe(ElementosPueblo) {
  return Huella{HUELLA_SIMPLE, HUELLA_SIMPLE};
}

bool esUnico(ElementosGranja tipo) {
  return tipo == ElementosGranja::Cabania ||
         tipo == ElementosGranja::EntradaMina ||
         tipo == ElementosGranja::SalidaPueblo;
}

bool esUnico(ElementosCaverna) { return true; }

bool esUnico(ElementosPueblo) { return true; }
