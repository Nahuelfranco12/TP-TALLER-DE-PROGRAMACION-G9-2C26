#include "mapa_editor.h"

#include <utility>

MapaEditor crearMapaPredeterminado(Dimensiones granja, Dimensiones caverna,
                                   Dimensiones pueblo) {
  std::vector<MapaZona<ElementosCaverna>> niveles(
      CANTIDAD_NIVELES_CAVERNA,
      MapaZona<ElementosCaverna>(caverna, Terreno::PisoCaverna));
  return MapaEditor{"", MapaZona<ElementosGranja>(granja, Terreno::Pasto),
                    std::move(niveles),
                    MapaZona<ElementosPueblo>(pueblo, Terreno::PisoPueblo)};
}
