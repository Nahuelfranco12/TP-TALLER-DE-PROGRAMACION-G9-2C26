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

CeldasOcupadasPorObjeto OcupadaPor(ElementosGranja tipo) {
  if (tipo == ElementosGranja::Cabania)
    return CeldasOcupadasPorObjeto{TAMANIO_OCUPADO_CABANIA_ANCHO,
                                   TAMANIO_OCUPADO_CABANIA_ALTO};
  if (tipo == ElementosGranja::Arbol1)
    return CeldasOcupadasPorObjeto{TAMANIO_OCUPADO_NORMAL,
                                   TAMANIO_OCUPADO_NORMAL};
  if (tipo == ElementosGranja::Arbol2)
    return CeldasOcupadasPorObjeto{TAMANIO_OCUPADO_ARBOL2,
                                   TAMANIO_OCUPADO_ARBOL2};
  return CeldasOcupadasPorObjeto{TAMANIO_OCUPADO_NORMAL,
                                 TAMANIO_OCUPADO_NORMAL};
}

CeldasOcupadasPorObjeto OcupadaPor(ElementosCaverna) {
  return CeldasOcupadasPorObjeto{TAMANIO_OCUPADO_NORMAL,
                                 TAMANIO_OCUPADO_NORMAL};
}

CeldasOcupadasPorObjeto OcupadaPor(ElementosPueblo tipo) {
  if (tipo == ElementosPueblo::CentroComunitario)
    return CeldasOcupadasPorObjeto{TAMANIO_OCUPADO_CENTROCOM_ANCHO,
                                   TAMANIO_OCUPADO_CENTROCOM_ALTO};

  return CeldasOcupadasPorObjeto{TAMANIO_OCUPADO_NORMAL,
                                 TAMANIO_OCUPADO_NORMAL};
}

bool esUnico(ElementosGranja tipo) {
  return tipo == ElementosGranja::Cabania ||
         tipo == ElementosGranja::EntradaMina ||
         tipo == ElementosGranja::SalidaPueblo;
}

bool esUnico(ElementosCaverna) { return true; }

bool esUnico(ElementosPueblo) { return true; }
