#ifndef IDS_PARTIDA_H_
#define IDS_PARTIDA_H_

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "constantes_persistencia.h"
#include "partida_guardada.h"

struct ClaveItem {
  ItemType tipo{};
  ItemSubtype subtipo{};

  bool operator==(const ClaveItem &) const = default;
};

template <typename T> using TablaIds = std::vector<std::pair<T, const char *>>;

const TablaIds<CropTypes> &tablaIds(CropTypes);
const TablaIds<AnimalType> &tablaIds(AnimalType);
const TablaIds<FurnitureType> &tablaIds(FurnitureType);
const TablaIds<CropQuality> &tablaIds(CropQuality);
const TablaIds<ClaveItem> &tablaIds(ClaveItem);

template <typename T> const char *idDe(const T &tipo) {
  for (const auto &[elemento, id] : tablaIds(T{}))
    if (elemento == tipo)
      return id;
  throw std::logic_error(ERROR_PARTIDA_SIN_ID);
}

template <typename T> T elementoDesdeId(const std::string &id) {
  for (const auto &[elemento, texto] : tablaIds(T{}))
    if (id == texto)
      return elemento;
  throw std::runtime_error(ERROR_PARTIDA_TIPO + id);
}

#endif // IDS_PARTIDA_H_
