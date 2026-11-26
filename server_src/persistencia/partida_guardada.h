#ifndef PARTIDA_GUARDADA_H_
#define PARTIDA_GUARDADA_H_

#include <cstddef>
#include <string>
#include <vector>

#include "../game/game_constants.h"
#include "../game/inventory/item.h"

struct OutfitGuardado {
  int gorro{};
  int pelo{};
  int remera{};
  int pantalon{};

  bool operator==(const OutfitGuardado &) const = default;
};

struct ItemGuardado {
  ItemType tipo{};
  ItemSubtype subtipo{};
  CropQuality calidad{};
  int cantidad{};

  bool operator==(const ItemGuardado &) const = default;
};

struct JugadorGuardado {
  std::string nombre;
  std::size_t indiceCabania{};
  OutfitGuardado outfit;
  double vida{};
  double energia{};
  int oro{};
  std::vector<ItemGuardado> inventario;

  bool operator==(const JugadorGuardado &) const = default;
};

struct CeldaGuardada {
  std::size_t x{};
  std::size_t y{};

  bool operator==(const CeldaGuardada &) const = default;
};

struct CultivoGuardado {
  CropTypes tipo{};
  std::size_t x{};
  std::size_t y{};
  std::size_t crecimiento{};
  std::size_t desdeRiego{};
  std::size_t conSed{};
  std::size_t maduro{};
  std::size_t cosechasExtra{};
  double suerte{};

  bool operator==(const CultivoGuardado &) const = default;
};

struct CofreGuardado {
  std::size_t x{};
  std::size_t y{};
  std::vector<ItemGuardado> inventario;

  bool operator==(const CofreGuardado &) const = default;
};

struct AnimalGuardado {
  AnimalType tipo{};
  std::size_t x{};
  std::size_t y{};
  bool listo{};

  bool operator==(const AnimalGuardado &) const = default;
};

struct GranjaGuardada {
  std::vector<CeldaGuardada> aradas;
  std::vector<CultivoGuardado> cultivos;
  std::vector<CofreGuardado> cofres;
  std::vector<AnimalGuardado> animales;

  bool operator==(const GranjaGuardada &) const = default;
};

struct PartidaGuardada {
  std::string nombre;
  std::string codigo;
  std::size_t dia{};
  bool multiplayer{};
  std::vector<JugadorGuardado> jugadores;
  GranjaGuardada granja;

  bool operator==(const PartidaGuardada &) const = default;
};

#endif // PARTIDA_GUARDADA_H_
