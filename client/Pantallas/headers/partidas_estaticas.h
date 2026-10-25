#ifndef PARTIDAS_ESTATICAS_H
#define PARTIDAS_ESTATICAS_H

#include <QString>
#include <QList>

struct PartidaGuardada {
    QString nombrePartida;
    QString nombrePersonaje;
    QString rutaImagen;
    bool esMultiplayer;
};

QList<PartidaGuardada> obtenerPartidasDePrueba();

#endif // PARTIDAS_ESTATICAS_H
