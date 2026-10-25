#ifndef PARTIDAS_ESTATICAS_H
#define PARTIDAS_ESTATICAS_H

#include <QList>
#include <QString>

struct MundoMock {
  QString nombreMundo;
  QString rutaImagen;
};

struct PartidaGuardada {
  QString nombrePartida;
  QString nombrePersonaje;
  QString rutaImagen;
  bool esMultiplayer = 0;
};

QList<PartidaGuardada> obtenerPartidasDePrueba();
QList<MundoMock> obtenerMundosDePrueba();

#endif // PARTIDAS_ESTATICAS_H
