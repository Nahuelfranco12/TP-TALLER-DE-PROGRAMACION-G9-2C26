#ifndef PARTIDAS_ESTATICAS_H
#define PARTIDAS_ESTATICAS_H

#include "datos_partida.h"
#include <QList>
#include <QString>

struct MundoMock {
  QString nombreMundo;
  QString rutaImagen;
};

struct PartidaGuardada {
  QString id;
  QString nombrePartida;
  DatosPersonaje personaje;
  bool esMultiplayer = false;
};

QList<PartidaGuardada> obtenerPartidasDePrueba();
QList<MundoMock> obtenerMundosDePrueba();

#endif // PARTIDAS_ESTATICAS_H
