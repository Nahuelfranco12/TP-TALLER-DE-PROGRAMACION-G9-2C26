#include "partidas_estaticas.h"

namespace {
const QString IMAGEN_PRUEBA =
    ":/pantallas/assets/Pantallas/02-nueva_partida_background.jpg";
const QString IMAGEN_MAPA_PRUEBA =
    ":/pantallas/assets/Pantallas/fondo_noche.png";
} // namespace

QList<PartidaGuardada> obtenerPartidasDePrueba() {
  return {
      {"1", "Granaj buen dia", {"Leon", 0, 0, 0, 0}, false},
      {"2", "se pelean los amigos", {"Lisandro", 1, 2, 1, 1}, true},
      {"3", "Aguante Boca", {"Nahuel", 2, 4, 2, 3}, true},
      {"4", "No se que mas poner", {"Camila", 5, 5, 3, 4}, true},
  };
}

QList<MundoMock> obtenerMundosDePrueba() {
  return {
      {"Granja1", IMAGEN_MAPA_PRUEBA},
      {"Granja2", IMAGEN_MAPA_PRUEBA},
  };
}
