#include "partidas_estaticas.h"

QList<PartidaGuardada> obtenerPartidasDePrueba() {
    QList<PartidaGuardada> lista;

    lista.append({"Granaj buen dia", "Leon", ":/ruta/a/tu/imagen_interrogacion.png", false});
    lista.append({"se pelean los amigos", "Lisandro", ":/ruta/a/tu/imagen_interrogacion.png", true});
    lista.append({"Aguante Boca", "Nahuel", ":/ruta/a/tu/imagen_interrogacion.png", true});
    lista.append({"No se que mas poner", "Camila", ":/ruta/a/tu/imagen_interrogacion.png", true});

    return lista;
}