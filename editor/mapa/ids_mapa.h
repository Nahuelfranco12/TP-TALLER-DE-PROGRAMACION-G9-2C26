#ifndef IDS_MAPA_H_
#define IDS_MAPA_H_

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "constantes_mapa.h"
#include "elementos_mapa.h"

template <typename T> using TablaIds = std::vector<std::pair<T, const char *>>;

const TablaIds<ElementosGranja> &tablaIds(ElementosGranja);
const TablaIds<ElementosCaverna> &tablaIds(ElementosCaverna);
const TablaIds<ElementosPueblo> &tablaIds(ElementosPueblo);

template <typename T> const char *idDe(T tipo) {
  for (const auto &[elemento, id] : tablaIds(T{}))
    if (elemento == tipo)
      return id;
  throw std::logic_error(TEXTO_ERROR_SIN_ID);
}

template <typename T> T tipoDesdeId(const std::string &id) {
  for (const auto &[elemento, texto] : tablaIds(T{}))
    if (id == texto)
      return elemento;
  throw std::runtime_error(TEXTO_ERROR_TIPO + id);
}

#endif // IDS_MAPA_H_
