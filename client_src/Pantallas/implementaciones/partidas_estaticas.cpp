#include "partidas_estaticas.h"

QList<PartidaGuardada> obtenerPartidasDePrueba() {
  return {
      {"1", "Granaj buen dia", {"Leon", 0, 0, 0, 0}, false},
      {"2", "se pelean los amigos", {"Lisandro", 1, 2, 1, 1}, true},
      {"3", "Aguante Boca", {"Nahuel", 2, 4, 2, 3}, true},
      {"4", "No se que mas poner", {"Camila", 5, 5, 3, 4}, true},
  };
}
