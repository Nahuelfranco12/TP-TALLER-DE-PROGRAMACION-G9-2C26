#include "partidas_estaticas.h"

namespace {
const QString IMAGEN_PRUEBA = ":/pantallas/assets/Pantallas/01-inicio_screen.png";
}

QList<PartidaGuardada> obtenerPartidasDePrueba() {
    return {
        {"Granaj buen dia", "Leon", IMAGEN_PRUEBA, false},
        {"se pelean los amigos", "Lisandro", IMAGEN_PRUEBA, true},
        {"Aguante Boca", "Nahuel", IMAGEN_PRUEBA, true},
        {"No se que mas poner", "Camila", IMAGEN_PRUEBA, true},
    };
}

QList<MundoMock> obtenerMundosDePrueba() {
    return {
        {"Granja1", IMAGEN_PRUEBA},
        {"Granja2 ", IMAGEN_PRUEBA},
    };
}
