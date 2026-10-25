#include "partidas_estaticas.h"

QList<PartidaGuardada> obtenerPartidasDePrueba() {
    QList<PartidaGuardada> lista;

    lista.append({"Granaj buen dia", "Leon", ":/pantallas/assets/Pantallas/01-inicio_screen.png", false});
    lista.append({"se pelean los amigos", "Lisandro", ":/pantallas/assets/Pantallas/01-inicio_screen.png", true});
    lista.append({"Aguante Boca", "Nahuel", ":/pantallas/assets/Pantallas/01-inicio_screen.png", true});
    lista.append({"No se que mas poner", "Camila", ":/pantallas/assets/Pantallas/01-inicio_screen.png", true});

    return lista;
}