#include "validacion_mapas.h"

#include <algorithm>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "constantes_mapa.h"

namespace {
template <typename T> int cantidadDe(const MapaZona<T> &zona, T tipo) {
  return static_cast<int>(
      std::ranges::count_if(zona.objetos(), [tipo](const auto &objeto) {
        return objeto.tipo == tipo;
      }));
}

bool esCabania(ElementosGranja tipo) {
  switch (tipo) {
  case ElementosGranja::Cabania1:
  case ElementosGranja::Cabania2:
  case ElementosGranja::Cabania3:
  case ElementosGranja::Cabania4:
  case ElementosGranja::Cabania5:
    return true;
  default:
    return false;
  }
}

std::string conEncabezado(const std::string &lugar, const std::string &mensaje) {
  return lugar + VALIDACION_TEXTO_SEPARADOR + mensaje;
}

std::string falta(const std::string &lugar, const char *nombre) {
  return conEncabezado(lugar, std::string(VALIDACION_TEXTO_FALTA) + nombre);
}

void validarGranja(const MapaZona<ElementosGranja> &granja,
                   std::vector<std::string> &errores) {
  int cabanias = static_cast<int>(
      std::ranges::count_if(granja.objetos(), [](const auto &objeto) {
        return esCabania(objeto.tipo);
      }));
  if (cabanias < VALIDACION_CABANIAS_MINIMAS)
    errores.push_back(conEncabezado(
        VALIDACION_TEXTO_ZONA_GRANJA,
        VALIDACION_TEXTO_CABANIAS_INICIO +
            std::to_string(VALIDACION_CABANIAS_MINIMAS) +
            VALIDACION_TEXTO_CABANIAS_FIN));
  if (cantidadDe(granja, ElementosGranja::SalidaPueblo) == 0)
    errores.push_back(falta(VALIDACION_TEXTO_ZONA_GRANJA, TEXTO_SALIDA_PUEBLO));
}

void validarPueblo(const MapaZona<ElementosPueblo> &pueblo,
                   std::vector<std::string> &errores) {
  static const std::vector<std::pair<ElementosPueblo, const char *>>
      obligatorios = {
          {ElementosPueblo::NpcMarnie, TEXTO_MARNIE},
          {ElementosPueblo::NpcClint, TEXTO_CLINT},
          {ElementosPueblo::NpcPierre, TEXTO_PIERRE},
          {ElementosPueblo::NpcRobin, TEXTO_ROBIN},
          {ElementosPueblo::CasaMarnie, TEXTO_CASA_MARNIE},
          {ElementosPueblo::CasaClint, TEXTO_CASA_CLINT},
          {ElementosPueblo::CasaPierre, TEXTO_CASA_PIERRE},
          {ElementosPueblo::CasaRobin, TEXTO_CASA_ROBIN},
          {ElementosPueblo::CentroComunitario, TEXTO_CENTRO_COMUNITARIO},
          {ElementosPueblo::SalidaGranja, TEXTO_SALIDA_GRANJA},
          {ElementosPueblo::EntradaMina, TEXTO_ENTRADA_MINA}};
  for (const auto &[tipo, nombre] : obligatorios)
    if (cantidadDe(pueblo, tipo) == 0)
      errores.push_back(falta(VALIDACION_TEXTO_ZONA_PUEBLO, nombre));
}

void validarCaverna(const std::vector<MapaZona<ElementosCaverna>> &niveles,
                    std::vector<std::string> &errores) {
  for (std::size_t i = 0; i < niveles.size(); ++i) {
    std::string nivel = std::string(VALIDACION_TEXTO_ZONA_CAVERMA) +
                        VALIDACION_TEXTO_NIVEL +
                        std::to_string(i + PRIMER_NIVEL_CAVERNA);
    if (cantidadDe(niveles[i], ElementosCaverna::SalidaCaverna) == 0)
      errores.push_back(falta(nivel, TEXTO_SALIDA_CAVERNA));
    bool esUltimo = i + 1 == niveles.size();
    if (!esUltimo && cantidadDe(niveles[i], ElementosCaverna::Escalera) == 0)
      errores.push_back(falta(nivel, TEXTO_ESCALERA));
  }
}
} // namespace

std::vector<std::string> erroresDe(const MapaEditor &mapa) {
  std::vector<std::string> errores;
  if (mapa.nombre.empty())
    errores.push_back(VALIDACION_TEXTO_ERROR_NOMBRE);
  validarGranja(mapa.granja, errores);
  validarPueblo(mapa.pueblo, errores);
  validarCaverna(mapa.nivelesCaverna, errores);
  return errores;
}
